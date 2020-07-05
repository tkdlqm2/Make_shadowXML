import argparse
import os
import time
import sys
from subprocess import check_output, Popen, PIPE
import datetime
import subprocess
from time import sleep
from threading import Thread

# addlibBITCOIND plugin at xml file.
def mining_option(num):
    target_so = "\"libBITCOIND" + num + ".so\">"
    comm = "\n\t<plugin id=\"NODE\" path="
    comm = comm + target_so + "\n"
    return comm

def exec_shell_cmd_system(cmd):
    if os.system(cmd) != 0:
        print("error while executing '%s'" % cmd)
        exit(-1)

def runtime_option(time):
    run_time = "\t<kill time="
    target = "\"" + time + "\""
    run_time = run_time + target + "/>" + "\n\n"
    return run_time

def set_bitcoind(node_count,f):
    first_line = "\t<node id="
    second_line = "\t\t<application plugin=\"NODE\" time=\"1\" arguments="
    last_line = "\t</node>\n\n"

    for i in range(1,node_count + 1):
        comm = "\"bleep" + str(i) + "\""
        firstline = first_line + comm + ">\n"
        f.write(firstline)

        comm = "\"-debug -listen=1 -testnet -datadir=data/bcdnode" + str(i) + " -noconnect -rpcuser=a -rpcpassword=1234 -rpcport=1000" + str(i) + " -port=111" + str(i) + " "
        secondline = second_line + comm

        for i in range(1,node_count + 1):
            comm = "-rpcallowip=11.0.0." + str(i) + " "
            secondline = secondline + comm
            comm = "-rpcbind=11.0.0." + str(i) + " "
            secondline = secondline + comm

        secondline = secondline + "\"\>\n"
        f.write(secondline)
        f.write(last_line)

def set_rpc(node_count,f):
    first_line = "\t<node id=\"rpc\">\n"
    second_line = "\t\t<application plugin=\"rpc\" time=\"5\" arguments="
    second_line = second_line + "\"" + str(node_count) + "\"" + "\>\n"
    last_line = "\t</node>\n\n"

    f.write(first_line)
    f.write(second_line)
    f.write(last_line)

if __name__ == '__main__':

    node_count = int(sys.argv[1]) # node counts
    f = open("/Users/csrc2020/Desktop/python_xml/example.xml","a")
    f.write(mining_option(sys.argv[3])) # set runtime
    f.write(runtime_option(sys.argv[2])) # set mining difficulty
    set_bitcoind(node_count,f)
    set_rpc(node_count,f)
    f.write("</shadow>")
    f.close()
    command = "shadow example"
    # exec_shell_cmd_system(command)
