/**
 * includes.h
 *
 * Author   Jonathan Lo <jcl5201>
 * necessary includes
 */

#ifndef _INCLUDES_H
#define _INCLUDES_H

// system include files

#include <cstdlib>
#include <iostream>
#include <stdio.h>

// 'arch' library

#include <Clock.h>
#include <Bus.h>
#include <StorageObject.h>
#include <Clearable.h>
#include <Counter.h>
#include <Constant.h>
#include <Memory.h>
#include <BusALU.h>

using namespace std;

// program-specific includes

#include "hardware.h"
#include "hw_fetch.h"
#include "hw_issue.h"
#include "hw_read.h"
#include "hw_exec.h"
#include "hw_mem.h"
#include "prototypes.h"

#endif

// $(filename) END
