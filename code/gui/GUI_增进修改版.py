import Tkinter
import os
from Tkinter import *
import threading


#Booleans
NO=FALSE=OFF=0
YES=TRUE=ON=1

# -anchor and -sticky
N='n'
S='s'
W='w'
E='e'
NW='nw'
SW='sw'
NE='ne'
SE='se'
NS='ns'
EW='ew'
NSEW='nsew'
CENTER='center'

# -fill
NONE='none'
X='x'
Y='y'
BOTH='both'

# -side
LEFT='left'
TOP='top'
RIGHT='right'
BOTTOM='bottom'

# -relief
RAISED='raised'
SUNKEN='sunken'
FLAT='flat'
RIDGE='ridge'
GROOVE='groove'
SOLID = 'solid'

# -orient
HORIZONTAL='horizontal'
VERTICAL='vertical'

# -tabs
NUMERIC='numeric'

# -wrap
CHAR='char'
WORD='word'

# -align
BASELINE='baseline'

# -bordermode

INSIDE='inside'
OUTSIDE='outside'

# Special tags, marks and insert positions

SEL='sel'
SEL_FIRST='sel.first'
SEL_LAST='sel.last'
END='end'
INSERT='insert'
CURRENT='current'
ANCHOR='anchor'
ALL='all' # e.g. Canvas.delete(ALL)

# Text widget and button states

NORMAL='normal'
DISABLED='disabled'
ACTIVE='active'

# Canvas state

HIDDEN='hidden'

# Menu item types

CASCADE='cascade'
CHECKBUTTON='checkbutton'
COMMAND='command'
RADIOBUTTON='radiobutton'
SEPARATOR='separator'

# Selection modes for list boxes

SINGLE='single'
BROWSE='browse'
MULTIPLE='multiple'
EXTENDED='extended'

# Activestyle for list boxes

# NONE='none' is also valid

DOTBOX='dotbox'
UNDERLINE='underline'

# Various canvas styles

PIESLICE='pieslice'
CHORD='chord'
ARC='arc'
FIRST='first'
LAST='last'
BUTT='butt'
PROJECTING='projecting'
ROUND='round'
BEVEL='bevel'
MITER='miter'

# Arguments to xview/yview

MOVETO='moveto'
SCROLL='scroll'
UNITS='units'
PAGES='pages'


def start_nav():
    os.system("")


def navigation():
    navi = Tkinter.Tk()
    navi.title("Autonomous_Navigation ")
    navi.geometry("250x250")
    b3 = Button(navi, text="Build_Map", command=mainctrl)
    b3.pack()

    bright = Button(navi, text="Start_Navigation", command=start_nav)
    bright.pack()
    navi.mainloop()


def tar_startControl():
    os.system("source ./devel/setup.bash")
    os.system("rosrun wpr_simulation keyboard_vel_ctrl")


def startControl():
    th = threading.Thread(target=tar_startControl)
    th.setDaemon(True)
    th.start()
    # time.sleep()


def tar_go_ahead():
    os.system("w")


def go_ahead():
    th = threading.Thread(target=tar_go_ahead)
    th.setDaemon(True)
    th.start()


def tar_go_backward():
    os.system("s -bash")


def go_backward():
    th = threading.Thread(target=tar_go_backward)
    th.setDaemon(True)
    th.start()


def go_left():
    os.system("a -bash")


def go_right():
    os.system("d -bash")


def turn_left():
    os.system("q -bash")


def turn_right():
    os.system("e -bash")


def stop():
    os.system("  -bash")
    os.system("x -bash")


def save_map():
    os.system("")


def controlInter():
    mc = Tkinter.Tk()
    mc.title("Control_Inter")
    mc.geometry("300x300")
    bup = Button(mc, text="Go_Ahead", command=go_ahead)
    bdown = Button(mc, text="Go_Backward", command=go_backward)
    bleft = Button(mc, text="Go_Left", command=go_left)
    bright = Button(mc, text="Go_Right", command=go_right)
    bturn_left = Button(mc, text="Turn_Left", command=turn_left)
    brurn_right = Button(mc, text="Turn_Right", command=turn_right)
    bstop = Button(mc, text="Stop", command=stop)
    bup.pack()
    bdown.pack()
    bleft.pack()
    bright.pack()
    bturn_left.pack()
    brurn_right.pack()
    bstop.pack()
    mc.mainloop()


def mainctrl():
    mc = Tkinter.Tk()
    mc.title("Active_Control ")
    mc.geometry("300x300")
    start = Button(mc, text="Start_Control", command=startControl)
    control_inter = Button(mc, text="control_inter", command=controlInter)
    save = Button(mc, text="Save_Map", command=save_map)
    start.pack()
    control_inter.pack()
    save.pack()
    mc.mainloop()


def signin():
    sin = Tkinter.Tk()
    sin.title("LogIn_Interface")
    sin.geometry("250x250")

    v1 = StringVar()
    e1 = Entry(sin, textvariable=v1, width=10)
    e1.grid(row=100, column=200, padx=1, pady=1)

    lable1 = Label(sin, text='Username:  ')
    lable1.grid(row=100, column=125)

    v2 = StringVar()
    e2 = Entry(sin, textvariable=v2, width=10)
    e2.grid(row=110, column=200, padx=1, pady=1)

    lable2 = Label(sin, text='Password:  ')
    lable2.grid(row=110, column=125)

    button1 = Button(sin, text="Log_In", command=sin.quit, activeforeground="black", bg="white", bd=5,
                     font=("Arial", 8), width=4, height=2)
    button1.grid(row=200, column=125)

    sin.mainloop()


def tar_open_robot():
    os.system("rosdep install --from-paths src --ignore-src --rosdistro=kinetic -y")
    os.system("catkin_make ")
    os.system("source ./devel/setup.bash")
    os.system("roslaunch wpr_simulation wpb_gmapping.launch")


def open_robot():
    # Start_Robot
    # os.system("test.txt")
    th = threading.Thread(target=tar_open_robot)
    th.setDaemon(True)
    th.start()


def tar_test():
    os.system("sudo gedit test.txt")


def test():
    th = threading.Thread(target=tar_test)
    th.setDaemon(True)
    th.start()


def root():
    root = Tkinter.Tk()
    root.title("Robot")
    root.geometry("1000x700")
    root.resizable(width=True, height=True)
    root.tk.eval('package require Tix')

    lable2 = Label(root, text="State", bg="gray", bd=10, font=("Arial", 12), width=12, height=3)
    lable2.pack(anchor=NE)

    lable3 = Label(root, text="Good_Running", bg="green", bd=10, font=("Arial", 12), width=12, height=3)
    lable3.pack(anchor=NE)

    lable1 = Label(root, text="Current_User", bg="gray", bd=10, font=("Arial", 12), width=12, height=3)
    lable1.pack(anchor=NW)

    button1 = Button(root, text="Log_Out", command=test, activeforeground="black", bg="white", bd=5, font=("Arial", 12),
                     width=8,
                     height=3)
    button1.pack(anchor=NW)

    button2 = Button(root, text="Log_In", command=signin, activeforeground="black", bg="white", bd=5,
                     font=("Arial", 12),
                     width=8, height=3)
    button2.pack(anchor=NW)

    button = Button(root, text='Emergency_Stop ', command=root.quit, activeforeground="black", activebackground='blue',
                    bg='red',
                    fg='white', width=16, height=4)
    button.pack(side=BOTTOM)

    buttonStart = Button(root, text="Start_Robot",
                         command=open_robot,
                         activeforeground="black", bg="white", bd=5,
                         font=("Arial", 12), width=20, height=3)
    buttonStart.pack(anchor=N)

    buttonctrl = Button(root, text="Active_Control ", command=mainctrl,
                        activeforeground="black", bg="white", bd=5,
                        font=("Arial", 12), width=20, height=3)
    buttonctrl.pack(anchor=N)

    buttonnavi = Button(root, text="Autonomous_Navigation ", command=navigation, activeforeground="black", bg="white",
                        bd=5,
                        font=("Arial", 12), width=20, height=3)
    buttonnavi.pack(anchor=N)

    root.mainloop()


if __name__ == "__main__":
    root()
