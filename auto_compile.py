import os
import sys

import time

import re
import argparse

if __name__ == "__main__":

    argparser = argparse.ArgumentParser(description='build')

    argparser.add_argument(
        '--template', '-t',
        help='build template',
        type=str)


    argparser.add_argument(
        '--kconfig', '-kconf',
        help='kconfig',
        type=int)
    
    argparser.add_argument(
        '--set', '-set',
        help='set',
        type=str,
        )
    argparser.add_argument(
            '--clean_all', '-clean_all',
            help='set',
            type=str,
            )

    args = argparser.parse_args()
    print(args)
    load_dev_cmd = 'source ~/.esp.sh'
    err = os.system(load_dev_cmd)
    if err:
        print("load dev failed")
        exit(-1)
    if args.kconfig:
        create_cmd = 'python kconfig.py'
        err = os.system(create_cmd)
        if err:
            print("execute kconfig error")
            exit(-1)
    else:
        print("execute without using kconfig")
    
    if(args.set):
        set_cmd = 'idf.py set-target {}'.format(args.set)
        os.system(set_cmd)
    if(args.clean_all):
        clean_cmd = 'idf.py fullclean'
        os.system(clean_cmd)

    build_cmd = 'idf.py build'
    os.system(build_cmd)
