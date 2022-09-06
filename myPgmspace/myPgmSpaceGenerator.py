
#---------------------------------------------
# Author: Tiago Lobao
# 
# License: GNU
#
# The script will generate big strings as unsigned char
# the main purpose is to be used in the memspace of the MCU
# generating it with python makes it easier to change/visualize
#---------------------------------------------

# -----------------------------------------------------------------------------------
# -----------------------------------------------------------------------------------
# Defined arrays. It's a dictionary where the key is the ID of the 
# string, and the value is the string itself
# -----------------------------------------------------------------------------------
# -----------------------------------------------------------------------------------

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
\n\r\
hi                                       displays this message\n\r\
\n\r\
dio [--flip=<pin>] [--set-high=<pin>]    changes the value of a dio pin\n\r\
    [--set-low=<pin>] [--show]\n\r\
\n\r\
led [--blink] [--clear-error]            changes the state of the builtin led\n\r\
                                         (used to show system state)\n\r\
''',

    "cmdResp_dioNotPossible":
'''\
error: unknown option for dio command\n\r\
''',

    "cmdResp_noCommand":
'''\
Command not found, try to say "hi" first.\n\r\
'''

}


# -----------------------------------------------------------------------------------
# -----------------------------------------------------------------------------------
# start of the script
# -----------------------------------------------------------------------------------
# -----------------------------------------------------------------------------------


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
 
#ifndef PGMEM_GEN_H
#define PGMEM_GEN_H

''')

    # ---------------------------- generated content ----------------------------

    #calculate the buffer size


    # write the index and the string in hex defines
    
    for myName,myStr in myDict.items():
        myLen = len(myStr)
        # +1 because the string ends with null
        f.write(f'''const uint8_t myPgmem_{myName}[{myLen+1}] PROGMEM = {'{'} ''')
        for myChar in myStr:
            f.write(f'''{hex(ord(myChar))},''')
        f.write(f'''0x00 {'}'};\n\n''')


    # write the declarations of the array of pointers
    f.write(f'''#define DECLARE_MY_PGMEM {'{'}\\\n''')
    myIndex = 0
    for myName,myStr in myDict.items():
        myIndex += 1
        if myIndex != myNumberOfArrays:
            f.write(f'''    myPgmem_{myName},\\\n''')
        else:
            #without comma, end of the array
            f.write(f'''    myPgmem_{myName}\\\n''')
    f.write(f'''{'}'}\n\n''')

    # write the declarations of the size of the arrays
    f.write(f'''#define DECLARE_MY_PGMEM_SIZES {'{'}\\\n''')
    myIndex = 0
    for myName,myStr in myDict.items():
        myLen = len(myStr)
        myIndex += 1
        if myIndex != myNumberOfArrays:
            f.write(f'''    {hex(myLen)},\\\n''')
        else:
            #without comma, end of the array
            f.write(f'''    {hex(myLen)}\\\n''')

    f.write(f'''{'}'}\n\n''')
    # ---------------------------- end of the file ----------------------------
    f.write('''#endif /* PGMEM_GEN_H */''')



with open('myPgmspace/myPgmspaceDefines.h', 'w') as f:

    f.write(f'''
/**************************************************************
 * Arduino Bencher
 *
 * @file myPgmspaceDefines.h
 *
 * @brief Generated file with defines for both module and application
 * Ids of each string
 *************************************************************/
 
#ifndef PGMEM_SHARE_H
#define PGMEM_SHARE_H

#define PGMEM_STR_CNT {myNumberOfArrays}u\n\n''')

    #write the ids's to be shared with the application
    myIndex = 0
    for myName,myStr in myDict.items():
        f.write(f'''{'#'}define myProgmem_{myName}_id {myIndex}u\n''')
        myIndex += 1

    f.write('''#endif /* PGMEM_SHARE_H */''')