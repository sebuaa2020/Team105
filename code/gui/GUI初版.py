import tkinter
from tkinter import *
from tkinter.tix import Tk, Control, ComboBox  #升级的组合控件包
from tkinter.messagebox import showinfo, showwarning, showerror #各种类型的提示框

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

root = Tk() 
root.title("hello tkinter")
root.geometry("1000x700")
root.resizable(width=True, height=True)
root.tk.eval('package require Tix')

lable2 = Label(root, text="状态", bg="gray",bd=10, font=("Arial",12), width=8, height=3)
lable2.pack(anchor = NE)

lable3 = Label(root, text="正常", bg="gray",bd=10, font=("Arial",12), width=8, height=3)
lable3.pack(anchor = NE)


lable1 = Label(root, text="当前用户", bg="gray",bd=10, font=("Arial",12), width=8, height=3)
lable1.pack(anchor = NW)

button1 = Button(root, text="注销", activeforeground="black", bg="white",bd=5, font=("Arial",12), width=8, height=3)
button1.pack(anchor = NW)

def signin():
    sin = Tk()
    sin.title("登录界面")
    sin.geometry("250x250")

    v1 = StringVar()
    e1 = Entry(sin,textvariable=v1,width=10)
    e1.grid(row=100,column=200,padx=1,pady=1)

    lable1=Label(sin,text='用户名：  ')
    lable1.grid(row=100,column=125)

    v2 = StringVar()
    e2 = Entry(sin,textvariable=v2,width=10)
    e2.grid(row=110,column=200,padx=1,pady=1)

    lable2=Label(sin,text='密码：  ')
    lable2.grid(row=110,column=125)

    button1 = Button(sin, text="登录", command = sin.quit, activeforeground="black", bg="white",bd=5, font=("Arial",8), width=4, height=2)
    button1.grid(row=200,column=125)

    sin.mainloop


button2 = Button(root, text="登录", command = signin, activeforeground="black", bg="white",bd=5, font=("Arial",12), width=8, height=3)
button2.pack(anchor = NW)

button=Button(root,text='紧急停止',command=root.quit,activeforeground="black",activebackground='blue',bg='red',fg='white', width=8, height=4)
button.pack(side = BOTTOM)

def mainctrl():
    mc = Tk()
    mc.title("主动控制")
    mc.geometry("250x250")
    bup = Button(mc, text="向上")
    bdown = Button(mc, text="向下")
    bleft = Button(mc, text="向左")
    bright = Button(mc, text="向右")
    bup.pack()
    bdown.pack()
    bleft.pack()
    bright.pack()
    mc.mainloop()

def navigation():
    navi = Tk()
    navi.title("自主导航")
    navi.geometry("250x250")
    b1 = Button(navi, text="显示位置")
    b1.pack()
    b2 = Button(navi, text="设置目标点")
    b2.pack()
    b3 = Button(navi, text="建立地图")
    b3.pack()

    bright = Button(navi, text="开始导航", )
    bright.pack()
    navi.mainloop()

buttonctrl = Button(root, text="主动控制", command= mainctrl , activeforeground="black", bg="white",bd=5, font=("Arial",12), width=8, height=3)
buttonctrl.pack(anchor = N)

buttonnavi = Button(root, text="自主导航", command= navigation , activeforeground="black", bg="white",bd=5, font=("Arial",12), width=8, height=3)
buttonnavi.pack(anchor = N)



root.mainloop()

