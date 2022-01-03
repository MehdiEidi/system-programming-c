// Package pid implements a pid manager. Acquiring and Releasing PIDs are implemented.
package pid

import (
	pidmap "a/pid-map"
	"errors"
	"sync"
)

const (
	MIN_PID = 300
	MAX_PID = 5000
)

// PIDs is a bit-map of PIDs. False means pid represented by that index is unused.
var PIDs *pidmap.PIDMap

var lock sync.Mutex

// AllocateMap initializes a new pid map.
func AllocateMap() {
	PIDs = pidmap.New(5000 - 300 + 1)
}

// AllocatePID marks an unused PID as used and returns it. It returns 0 and an error if no PID was available.
func AllocatePID() (int, error) {
	lock.Lock()
	defer lock.Unlock()

	for i := range PIDs.PIDs {
		if !PIDs.State(i) {
			PIDs.SetState(i, true)
			return i, nil
		}
	}

	return 0, errors.New("no PID available")
}

// ReleasePID sets the state of the given pid as available.
func ReleasePID(pid int) {
	PIDs.SetState(pid, false)
}
