/* -*- c++ -*- */

#define DZLABS_API

%include "gnuradio.i"			// the common stuff

//load generated python docstrings
%include "dzlabs_swig_doc.i"

%{
#include "dzlabs/udp_sink.h"
#include "dzlabs/udp_source.h"
#include "dzlabs/iq_injector.h"
%}



%include "dzlabs/udp_sink.h"
GR_SWIG_BLOCK_MAGIC2(dzlabs, udp_sink)

%include "dzlabs/udp_source.h"
GR_SWIG_BLOCK_MAGIC2(dzlabs, udp_source)

%include "dzlabs/iq_injector.h"
GR_SWIG_BLOCK_MAGIC2(dzlabs, iq_injector)
