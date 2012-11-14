/**************************************************************************************
Copyright © 2007-2012 Omek Interactive Ltd. All Rights Reserved.

By including this header file in your application or project you agree to be 
bound by the Beckon API EULA [Beckon-SDK install dir/beckon_eula.txt]. 
If you do not have authority, or if you do not agree with the terms of the Beckon API EULA, 
you may not access or use the API. 
You should read and keep a copy of the EULA for your records.

The coded instructions, statements, computer programs, and/or related material (collectively 
"Data") in these files contain unpublished information proprietary to Omek Interactive Ltd., 
("Omek") which is protected by national and international copyright laws and by international 
treaties.

The Data may not be disclosed or distributed to third parties, in whole or in part, without the 
prior written consent of Omek.

OMEK DOES NOT GUARANTEE NOR MAKE ANY REPRESENTATION REGARDING THE USE OF, OR THE RESULTS OF THE 
USE OF THE DATA OR OMEK'S SERVICES, IN TERMS OF CORRECTNESS, ACCURACY OR OTHERWISE. THE DATA IS 
LICENSED "AS IS" AND WITHOUT WARRANTY.   OMEK SPECIFICALLY DISCLAIMS ALL WARRANTIES OR CONDITIONS 
WITH RESPECT TO THE DATA OR THE USE OR OPERATION THEREOF, WHETHER EXPRESS, IMPLIED,STATUTOR, ARISING 
BY CUSTOM OR TRADE USAGE, OR OTHERWISE, INCLUDING WITHOUT LIMITATION THE IMPLIED WARRANTIES OF 
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE OR USE AND NONINFRINGEMENT. WITHOUT LIMITING THE 
FOREGOING, OMEK DOES NOT WARRANT THAT THE OPERATION OF THE DATA WILL BE UNINTERRUPTED OR ERROR FREE.

IN NO EVENT WILL OMEK, ITS LICENSORS OR SUPPLIERS BE LIABLE FOR ANY DIRECT OR INDIRECT DAMAGES, COSTS, 
CLAIMS OR EXPENSES (INCLUDING WITHOUT LIMITATION LOST REVENUE, PROFIT OR DATA OR OTHER SPECIAL, INDIRECT, 
CONSEQUENTIAL, INCIDENTAL OR PUNITIVE DAMAGES HOWEVER CAUSED AND REGARDLESS OF THE THEORY OF LIABILITY, 
WHETHER FOR BREACH OF CONTRACT, TORT, INFRINGEMENT OR OTHERWISE), EVEN IF OMEK HAS BEEN ADVISED OF THE 
POSSIBILITY OF SUCH DAMAGES.  
**************************************************************************************/

#pragma once

#include "Shadow/Platform.h"
#include "Shadow/IFiredEvent.h"

namespace Omek 
{
/** 
@class IGestureListener IGestureListener.h "include/Shadow/IGestureListener.h"
@brief Interface for gesture events callbacks

This interface should be implemented by any class that handles the fired gestures
*/
class _ShadowExport IGestureListener
{
public:
	/** Callback method called when the requested gesture is fired
		
		@param[out] gesture class holding the information about the fired gesture
		@see Gesture
	*/
	virtual void onGesture(const IFiredEvent *gesture) = 0;
};
}