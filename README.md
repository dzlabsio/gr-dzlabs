# gr-dzlabs

A collection of custom GNURadio blocks and scripts.

## AddBlock.py

Adds a new block to an OOT module with better formatting than the current `gr_modtool` template. Below is an example usage for adding the block `beef` the OOT module `gr-dead`:

```bash
$ gr_modtool newmod dead
$ cd gr-dzlabs/
gr-dzlabs/$ cd scripts
gr-dzlabs/scripts/$ ./AddBlock ../../gr-dead beef
===========================================
  GNURadio OOT Module Block Creation Tool  
===========================================
MODBASE:   dead
BLOCKNAME: beef
[*] writing file   : ../../gr-dead/grc/dead_beef.xml
[*] writing file   : ../../gr-dead/include/dead/beef.h
[*] writing file   : ../../gr-dead/lib/beef_impl.h
[*] writing file   : ../../gr-dead/lib/beef_impl.cc
[*] writing file   : ../../gr-dead/python/qa_beef.py
[*] modifying file : ../../gr-dead/grc/CMakeLists.txt
[*] modifying file : ../../gr-dead/include/dead/CMakeLists.txt
[*] modifying file : ../../gr-dead/lib/CMakeLists.txt
[*] modifying file : ../../gr-dead/python/CMakeLists.txt
[*] modifying file : ../../gr-dead/swig/dead_swig.i
```

**TODO**: allow custom block parameters and ports. For now, the block has the following constructor/interface/"options":

```C++
beef_impl(
    int arg0,
    char* arg1,
    bool arg2);
```

It also has two ports: an `in` port and an `out` port, both of which use the `pmt::pmt_t` PDU ("message") data type.
