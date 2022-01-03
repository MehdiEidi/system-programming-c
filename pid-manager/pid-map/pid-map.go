package pidmap

import "sync"

type PIDMap struct {
	Lock sync.Mutex
	PIDs []bool
}

func New(size int) *PIDMap {
	return &PIDMap{sync.Mutex{}, make([]bool, size)}
}

func (p *PIDMap) State(i int) bool {
	p.Lock.Lock()
	defer p.Lock.Unlock()
	return p.PIDs[i]
}

func (p *PIDMap) SetState(i int, state bool) {
	p.Lock.Lock()
	defer p.Lock.Unlock()
	p.PIDs[i] = state
}
