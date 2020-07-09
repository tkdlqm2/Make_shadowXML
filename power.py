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
    target_so = "\"libBITCOIND.so\"/>"
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

        rpc_argv = 10000 + i
        port_argv = 1110 + i
        print(port_argv)
        comm = "\"-debug -listen=1 -testnet -datadir=data/bcdnode" + str(i) + " -noconnect -rpcuser=a -rpcpassword=1234 -rpcport=" + str(rpc_argv) + " -port=" + str(port_argv) + " "
        secondline = second_line + comm
        comm = "-rpcallowip=11.0.0." + str(i) + "/0 "
        secondline = secondline + comm
        comm = "-rpcbind=11.0.0." + str(i) + " "
        secondline = secondline + comm

        secondline = secondline + "\"/>\n"
        f.write(secondline)
        f.write(last_line)

def set_rpc(node_count,f):
    first_line = "\t<node id=\"rpc\">\n"
    second_line = "\t\t<application plugin=\"rpc\" time=\"5\" arguments="
    second_line = second_line + "\"" + str(node_count) + "\"" + "/>\n"
    last_line = "\t</node>\n\n"

    f.write(first_line)
    f.write(second_line)
    f.write(last_line)

def make_datadir(node_count):
    exec_shell_cmd_system("rm -rf data")
    exec_shell_cmd_system("mkdir data")
    exec_shell_cmd_system("cd data")
    for i in range(1,node_count+1):
        bcd = "bcdnode" + str(i)
        command = "mkdir " + bcd
        exec_shell_cmd_system(command)

        command = "mv " + bcd + " data"
        exec_shell_cmd_system(command)

def make_result_rpc(node_count, f, run_time):
    target_time = run_time - 2
    IP_format = "11.0.0."
    for i in range(1,node_count + 1):
        port_format = 10000 + i

        first_line = "\t<node id="
        comm = "\"result" +str(i) + "\""
        first_line = first_line + comm + ">\n"

        second_line = "\t\t<application plugin=\"rpc2\" "
        comm = "time=\"" + str(target_time) +"\" arguments="
        second_line = second_line + comm

        comm = "\""
        second_line = second_line + comm

        comm = IP_format + str(i) + ":"
        second_line = second_line + comm
        comm = str(port_format)
        second_line = second_line + comm + "\""
        second_line = second_line + "/>\n"

        last_line = "\t</node>\n\n"

        f.write(first_line)
        f.write(second_line)
        f.write(last_line)

if __name__ == '__main__':

    node_count = int(sys.argv[1]) # node counts
    exec_shell_cmd_system("rm -rf example3.xml")
    exec_shell_cmd_system("cp example.xml example3.xml")
    f = open("/Users/csrc2020/Desktop/python_xml/example3.xml","a")
    f.write(mining_option(sys.argv[3])) # set mining difficulty
    f.write(runtime_option(sys.argv[2])) # set runtime_option
    set_bitcoind(node_count,f)
    set_rpc(node_count,f)
    make_result_rpc(node_count, f, int(sys.argv[2]))
    f.write("</shadow>")
    f.close()
    make_datadir(int(sys.argv[1]))
    command = "shadow example3.xml"
    # exec_shell_cmd_system(command)