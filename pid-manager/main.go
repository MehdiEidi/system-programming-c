package main

import (
	"a/pid-manager"
	"fmt"
	"log"
	"math/rand"
	"sync"
	"time"
)

func main() {
	pid.AllocateMap()

	var wg sync.WaitGroup

	for i := 0; i < 100; i++ {
		wg.Add(1)

		go func() {
			r := rand.New(rand.NewSource(time.Now().UnixNano()))

			got, err := pid.AllocatePID()
			if err != nil {
				log.Println(err)
			}

			fmt.Println("Acquired PID:", got)

			time.Sleep(time.Duration(r.Intn(10) * int(time.Second)))

			pid.ReleasePID(got)
			fmt.Println("----Released PID:", got)

			wg.Done()
		}()
	}

	wg.Wait()
}
