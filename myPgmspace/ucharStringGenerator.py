
#---------------------------------------------
# Author: Tiago Lobao
# 
# License: GNU
#
# The script will generate big strings as unsigned char
# the main purpose is to be used in the memspace of the MCU
# generating it with python makes it easier to change/visualize
#---------------------------------------------

# Defined arrays. It's a dictionary where the key is the ID of the 
# string, and the value is the string itself

myDict = {
    
    "startMessage": 
'''\
serialUi started!\n\r\
Welcome to Arduino Bencher\n\r\
By: Tiago Lobao\n\r\
''',

    "cmdResp_hello":
'''\
Hello! I'm the Arduino Bencher!\n\r\
here are the list of commands you can type:\n\r\
~~comming soon~~\n\r\
'''

}

with open('myPgmspace/myGeneratedPgmSpace.h', 'w') as f:

    myNumberOfArrays = len(myDict)

    # ---------------------------- Beginning of the file ----------------------------
    f.write(f'''
/**************************************************************
 * Arduino Bencher
 *
 * @file myGeneratedPgmSpace.h
 *
 * @brief Generated files with big strings/vars, to be used in console
 * UI and pgmSpace
 *************************************************************/
 
#ifndef PGMEM_H
#define PGMEM_H

#define PGMEM_STR_CNT {myNumberOfArrays}u\n\n''')

    # ---------------------------- generated content ----------------------------

    #calculate the buffer size


    # write the index and the string in hex defines
    myIndex = 0
    for myName,myStr in myDict.items():

        # +3 because the first two elements is the size, and the last element is the NUL char
        myLen = len(myStr) + 3

        f.write(f'''{'#'}define {myName}_id {myIndex}u\n''')
        f.write(f'''const uint8_t myPgmem_{myName}[{myLen}] PROGMEM = {'{'} ''')
        f.write(f'''{hex(myLen)},0x00,  ''')
        for myChar in myStr:
            f.write(f'''{hex(ord(myChar))},''')
        f.write(f'''0x00 {'}'};\n\n''')
        myIndex += 1

    # write the declarations of the array of pointers
    f.write(f'''#define DECLARE_MY_PGMEM {'{'}\\\n''')
    for myName,myStr in myDict.items():
        f.write(f'''    myPgmem_{myName},\\\n''')
    f.write(f'''0u\\\n''')
    f.write(f'''{'}'}\n\n''')
    # ---------------------------- end of the file ----------------------------
    f.write('''#endif /* PGMEM_H */''')