#!/usr/bin/env python
import urllib,urllib2,httplib2,cookielib
import re,serial,time,threading,getpass


username=raw_input("ASURITE ID: ")
print "%s, Enter Your " % username, 
password = getpass.getpass()

oldnumber=0
number=0
class Timer(threading.Thread):
    def __init__(self, seconds, action):
 	self.runTime = seconds
 	self.action = action
 	threading.Thread.__init__(self)
    def run(self):
	time.sleep(self.runTime)
	self.action()

def Connect():
    for i in range(0, 25):
        try:
            ser = serial.Serial(i,9600, timeout=2)
            ser.write("1!")
            if ser.read(4)=="Ping":
                return i
                break
        except:
            if i>=25 or i=="None":
                try:
                    ser = serial.Serial("/dev/ttyUSB0",9600,timeout=2)
                    ser.write("1!")
                    if ser.read(4)=="Ping":
                        return "/dev/ttyUSB0"
                        break
                except:
                    return "Fail"
                    break
                    pass
def GetData():
    global TimerOn
    global Digit1
    global Digit2
    global oldnumber, number, update
    
    cj = cookielib.CookieJar()
    opener = urllib2.build_opener(urllib2.HTTPCookieProcessor(cj))
    login_data = urllib.urlencode({'userid' : username, 'password' : password, 'Login':'Login', 'callapp':'https://webapp4.asu.edu/corda/dashboards/CRMSupportDashboard/pages/summary.pagexml'})
    login= opener.open('https://weblogin.asu.edu/cgi-bin/login?callapp=https://webapp4.asu.edu/corda/dashboards/CRMSupportDashboard/pages/summary.pagexml', login_data)
    txt= login.read()

    re1='(\\()'	# (
    re2='(\\d)'	# #
    re3='(\\d)'	# #
    re4='(\\))'	# )
    rg = re.compile(re1+re2+re3+re4,re.IGNORECASE|re.DOTALL)
    m = rg.search(txt)

    if m:
        c1=m.group(1)
        int1=m.group(2)
        int2=m.group(3)
        c2=m.group(4)
        Digit1=int1
        Digit2=int2
        
        oldnumber=number
        number=((int(Digit1)*10)+int(Digit2))
        if (number == oldnumber):
            update=0
        if (number > oldnumber):
            update=2   
        if (number < oldnumber):
            update=3
        TimerOn=False


if __name__ == '__main__':
    global TimerOn
    global Digit1
    global Digit2
    global update

    ser = None
        
    print "\nFinding CRM Module Please Wait..."
    Port=Connect()    
    if Port=="Fail":
        print "Connect failed! Check USB Link..."
        sys.exit(0)
    else:
        print "USB Link Established PORT:"+str(Port+1)
    
    TimerOn=False
    ser = serial.Serial(Port, 9600)
    GetData()
    
    while 1:
        if (TimerOn!=True):
            TimerOn=True
            c = Timer(60, GetData)
            c.start()

        if (update == 0):
            ser.write(str(update)+".")
        else:
            ser.write(str(update)+"."+str(Digit1)+"."+str(Digit2)+".")
        update=0
        Resp=ser.read(4)









