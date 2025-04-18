// OpenSTA, Static Timing Analyzer
// Copyright (c) 2025, Parallax Software, Inc.
// 
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program. If not, see <https://www.gnu.org/licenses/>.
// 
// The origin of this software must not be misrepresented; you must not
// claim that you wrote the original software.
// 
// Altered source versions must be plainly marked as such, and must not be
// misrepresented as being the original software.
// 
// This notice may not be removed or altered from any source distribution.

#pragma once

#include "Vector.hh"
#include "StringSeq.hh"
#include "NetworkClass.hh"
#include "GraphClass.hh"
#include "SdcClass.hh"
#include "StaState.hh"

namespace sta {

typedef StringSeq CheckError;
typedef Vector<CheckError*> CheckErrorSeq;

class CheckTiming : public StaState
{
public:
  explicit CheckTiming(StaState *sta);
  ~CheckTiming();
  CheckErrorSeq &check(bool no_input_delay,
		       bool no_output_delay,
		       bool reg_multiple_clks,
		       bool reg_no_clks,
		       bool unconstrained_endpoints,
		       bool loops,
		       bool generated_clks);

protected:
  void clear();
  void deleteErrors();
  void checkNoInputDelay();
  void checkNoOutputDelay();
  void checkRegClks(bool reg_multiple_clks,
		    bool reg_no_clks);
  void checkUnconstrainedEndpoints();
  bool hasClkedArrival(Vertex *vertex);
  void checkNoOutputDelay(PinSet &ends);
  void checkUnconstraintedOutputs(PinSet &unconstrained_ends);
  void checkUnconstrainedSetups(PinSet &unconstrained_ends);
  void checkLoops();
  bool hasClkedDepature(Pin *pin);
  bool hasClkedCheck(Vertex *vertex);
  bool hasMaxDelay(Pin *pin);
  void checkGeneratedClocks();
  void pushPinErrors(const char *msg,
		     PinSet &pins);
  void pushClkErrors(const char *msg,
		     ClockSet &clks);
  void errorMsgSubst(const char *msg,
		     int count,
		     std::string &error_msg);

  CheckErrorSeq errors_;
};

} // namespace
