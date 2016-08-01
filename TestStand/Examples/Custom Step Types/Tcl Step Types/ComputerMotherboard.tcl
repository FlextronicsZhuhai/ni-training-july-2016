puts "Which of the following tests do you want to fail? (Type Y to fail the test)"
puts "Power On"
gets stdin powerOnFail
if {[expr [string length $powerOnFail] ==0]} {set powerOnFail "N"}
puts "Video"
gets stdin videoFail
if {[expr [string length $videoFail] ==0]} {set videoFail "N"}
puts "CPU"
gets stdin cpuFail
if {[expr [string length $cpuFail] ==0]} {set cpuFail "N"}
puts "ROM"
gets stdin romFail
if {[expr [string length $romFail] ==0]} {set romFail "N"}
puts "RAM"
gets stdin ramFail
if {[expr [string length $ramFail] ==0]} {set ramFail "N"}
puts "Keyboard"
gets stdin keyboardFail
if {[expr [string length $keyboardFail] ==0]} {set keyboardFail "N"}