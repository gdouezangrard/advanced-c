#!/usr/bin/python


import sys
import subprocess
import tempfile
import os
import os.path
import select 
import time
import shutil


os.environ["PATH"]=os.environ["PATH"]+":"+os.getcwd()

print os.getenv("PATH")

DELTA=20

def get_win_pos(id):
    o=subprocess.check_output(["xwininfo","-id",id])
    lines=o.split("\n")
    for l in lines:
        if "Absolute upper-left X:" in l:
            x=int(l.split()[3])
        elif "Absolute upper-left Y:" in l:
            y=int(l.split()[3])
        elif "Width:" in l:
            w=int(l.split()[1])
        elif "Height:" in l:
            h=int(l.split()[1])
    return (x,y+h/2,x+w,y+h/2)

def filter_messages(msg,x,y,cid):
    global DELTA
    #print "filter messages :",msg,x,y,cid,DELTA
    r=[]
    for m in msg:
        if abs(m["x"]-x)<DELTA and abs(m["y"]-y)<DELTA and m["src"]!=cid:
            r.append(dict(m))
    #print "found",r
    return r

def add_message(msgs,m):
    global DELTA
    i=0
    while i<len(msgs):
        if abs(msgs[i]["x"]-m['x'])<DELTA*2 and abs(msgs[i]["y"]-m['y'])<DELTA*2 and msgs[i]["src"]==m["src"]:
            del msgs[i]
        else:
            i+=1        
    msgs.append(m)
    

prog_name=sys.argv[1]
n_blocks=int(sys.argv[2])


#create working directory
working_directory=tempfile.mkdtemp()
infos=[]
#create subworking dir:
for i in range(n_blocks):
    pdir=os.path.join(working_directory,str(i))
    os.mkdir(pdir)
    #create fifo for communication
    #two per blocks:
    fto=os.path.join(pdir,"boggle_from")
    os.mkfifo(fto,0600)
    ffrom=os.path.join(pdir,"boggle_to")
    os.mkfifo(ffrom,0600)
    # run the client
    print pdir
    env=dict(os.environ)
    env["BOGGLE_ID"]=str(i)
    client=subprocess.Popen(["xterm","-geometry","40x5","-title","boggle:"+str(i),prog_name,],cwd=pdir,env=env)
    infos.append({"to":fto,"from":ffrom,"process":client})
# now open fifo
rfds=[0]
wfds=[]
r_to_w={}
for info in infos:
    print info
    print "opening ",info["to"]
    info["to_file"]=os.open(info["to"],os.O_WRONLY)
    wfds.append(info["to_file"])
    print "opening ",info["from"]
    info["from_file"]=os.open(info["from"],os.O_RDONLY)
    rfds.append(info["from_file"])
    r_to_w[info["from_file"]]=info["to_file"]
    print "opened"

#finally get windows ids
for i in range(n_blocks):
    x=subprocess.check_output(['xwininfo','-name','boggle:'+str(i)])
    x=x.split('\n')[1]
    x=x.split()[3]
    infos[i]["window"]=x
    print get_win_pos(x)

#cleanup working directory
shutil.rmtree(working_directory)

messages_to_send=[]
messages_available=[]
IN_GAME=False
while True:
    r,w,e=select.select(rfds,wfds,[],1000)
    # cleanup pending messages
    while len(messages_available)>0 and (time.time()-messages_available[0]["time"])>1:
        del messages_available[0]
    #print "messages are:",messages_available
    for fd in r:
        msg=os.read(fd,200)
        msg=msg.strip()
        if msg=="":
            print "client disconnected"
            sys.exit(0)
        if fd==0:
            if msg=="play":
                if IN_GAME==False:
                    for f in wfds:
                        messages_to_send.append((f,"START"))
                    #IN_GAME=True
                else:
                    print "game already started"
            elif msg=="quit":
                print "bye"
                sys.exit(0)
            else:
                print "unkow command"
        else:
            #print "read from ",fd,msg
            msgs=msg.split('\n')
            for msg in msgs:
                #print "dealing with message ",msg
                msg=msg.split()
                client_pos=get_win_pos(infos[int(msg[1])]["window"])
                if msg[0]=="RL" or msg[0]=="RR":
                    if  msg[0]=="RL":
                        x=client_pos[0]
                        y=client_pos[1]
                    else:
                        x=client_pos[2]
                        y=client_pos[3]
                    fmsgs=filter_messages(messages_available,x,y,msg[1])
                    if len(fmsgs)>0:
                        for m in fmsgs:
                            messages_to_send.append((r_to_w[fd],m["data"]))
                    else:
                        messages_to_send.append((r_to_w[fd]," "))
                elif msg[0]=="WL":
                    #print "write left"
                    add_message(messages_available,{"data":msg[2],"x":client_pos[0],"y":client_pos[1],"time":time.time(),"src":msg[1]})
                elif msg[0]=="WR":
                    #print "write right"
                    add_message(messages_available,{"data":msg[2],"x":client_pos[2],"y":client_pos[3],"time":time.time(),"src":msg[1]})
                else:
                    print "unkow command ",msg[0]," from ",cid
#            messages.append((r_to_w[fd],"world"))
    i=0
    while i <len(messages_to_send):
        if messages_to_send[i][0] in w:
            os.write(messages_to_send[i][0],messages_to_send[i][1])
            del messages_to_send[i]
        else:
            i+=1
#messages_to_send=[]
