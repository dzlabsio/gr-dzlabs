#!/usr/bin/python3

import os
import sys



def MakeReplacements(modpath, modname, blockname, path_in):

    path_out = path_in
    path_out = path_out.replace("dead", modname)
    path_out = path_out.replace("beef", blockname)
    full_path_out = os.path.join(modpath, path_out)
    print("[*] writing file   : %s" % full_path_out)

    head, tail = os.path.split(path_in)
    fp = open(os.path.join("templates/", tail), "r")
    old = fp.read()
    fp.close()

    new = old
    new = new.replace("dead", modname)
    new = new.replace("DEAD", modname.upper())
    new = new.replace("beef", blockname)
    new = new.replace("BEEF", blockname.upper())

    fp = open(full_path_out, "w")
    fp.write(new)
    fp.close()



def main():

    print("===========================================")
    print("  GNURadio OOT Module Block Creation Tool  ")
    print("===========================================")

    if (len(sys.argv) != 3):
        print("usage: %s <oot-path> <block-name>" % sys.argv[0], file=sys.stderr)
        print("  EX:  %s ../../gr-adsb dl_demod_fm" % sys.argv[0], file=sys.stderr)
        sys.exit(-1)

    if os.path.isdir("templates") == False:
        print("[!] failed to find templates directory", file=sys.stderr)
        sys.exit(-1)

    MODPATH = sys.argv[1]
    if os.path.isdir(MODPATH) == False:
        print("[!] could not find OOT module path", file=sys.stderr)
        sys.exit(-1)

    if MODPATH[-1] == '/': # strip trailing slash if necessary (from terminal auto-complete)
        MODPATH = MODPATH[:-1]

    MODBASEGR = os.path.split(MODPATH)[1]
    if MODBASEGR[0:3] != "gr-":
        print("[!] not a valid OOT module (should start with \"gr-\")", file=sys.stderr)
        sys.exit(-1)

    MODBASE = MODBASEGR[3:]
    BLOCKNAME = sys.argv[2]
    print("MODBASE:   %s" % MODBASE)
    print("BLOCKNAME: %s" % BLOCKNAME)

    #=================#
    #  content files  #
    #=================#
    MakeReplacements(MODPATH, MODBASE, BLOCKNAME, "grc/dead_beef.xml")
    MakeReplacements(MODPATH, MODBASE, BLOCKNAME, "include/dead/beef.h")
    MakeReplacements(MODPATH, MODBASE, BLOCKNAME, "lib/beef_impl.h")
    MakeReplacements(MODPATH, MODBASE, BLOCKNAME, "lib/beef_impl.cc")
    MakeReplacements(MODPATH, MODBASE, BLOCKNAME, "python/qa_beef.py")

    #======================#
    #  grc/CMakeLists.txt  #
    #======================#
    full_path = os.path.join(MODPATH, "grc/CMakeLists.txt")
    print("[*] modifying file : %s" % full_path)

    fp = open(full_path, "r")
    text = fp.read()
    fp.close()

    search_term = "DESTINATION" 
    split_text = text.split(search_term)
    new_text = split_text[0] + MODBASE + "_" + BLOCKNAME + ".xml\n    " + search_term + split_text[1]

    fp = open(full_path, "w")
    fp.write(new_text)
    fp.close()

    #==========================#
    #  include/CMakeLists.txt  #
    #==========================#
    full_path = os.path.join(MODPATH, "include/dead/CMakeLists.txt".replace("dead", MODBASE))
    print("[*] modifying file : %s" % full_path)

    fp = open(full_path, "r")
    text = fp.read()
    fp.close()

    search_term = "DESTINATION"
    split_text = text.split(search_term)
    new_text = split_text[0] + BLOCKNAME + ".h\n    " + search_term + split_text[1]

    fp = open(full_path, "w")
    fp.write(new_text)
    fp.close()

    #======================#
    #  lib/CMakeLists.txt  #
    #======================#
    full_path = os.path.join(MODPATH, "lib/CMakeLists.txt")
    print("[*] modifying file : %s" % full_path)

    fp = open(full_path, "r")
    text = fp.read()
    fp.close()

    search_term = ")\n\nset(dead_sources \"${dead_sources}\" PARENT_SCOPE)".replace("dead", MODBASE)
    split_text = text.split(search_term)
    new_text = split_text[0] + "    " + BLOCKNAME + "_impl.cc\n" + search_term + split_text[1]

    fp = open(full_path, "w")
    fp.write(new_text)
    fp.close()

    #=========================#
    #  python/CMakeLists.txt  #
    #=========================#
    full_path = os.path.join(MODPATH, "python/CMakeLists.txt")
    print("[*] modifying file : %s" % full_path)

    fp = open(full_path, "r")
    text = fp.read()
    fp.close()

    new_text = text + "GR_ADD_TEST(qa_beef ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/qa_beef.py)".replace("beef", BLOCKNAME) + "\n"

    fp = open(full_path, "w")
    fp.write(new_text)
    fp.close()

    #=======================#
    #  swig/MODNAME_swig.i  #
    #=======================#
    full_path = os.path.join(MODPATH, "swig/dead_swig.i".replace("dead", MODBASE))
    print("[*] modifying file : %s" % full_path)

    fp = open(full_path, "r")
    text = fp.read()
    fp.close()

    search_term = "%}"
    split_text = text.split(search_term)
    new_text = split_text[0] + "#include \"" + MODBASE + "/" + BLOCKNAME + ".h\"\n" + search_term + split_text[1]
    new_text += "\n%include \"" + MODBASE + "/" + BLOCKNAME + ".h\"\n"
    new_text += "GR_SWIG_BLOCK_MAGIC2(" + MODBASE + ", " + BLOCKNAME + ")\n"

    fp = open(full_path, "w")
    fp.write(new_text)
    fp.close()



if __name__ == "__main__":
    main()
