package main

import (
	"fmt"
	"math/rand"
	"runtime"
	"sync"
	"time"
)

var (
	// insidePoints is the number of random points fell inside the circle.
	insidePoints int

	lock sync.Mutex
)

func main() {
	rand.Seed(time.Now().UnixNano())

	now := time.Now()

	fmt.Println("--- serial execution ---")
	fmt.Println("with 100000000 points. PI =", serialEstimatePI(100000000))

	fmt.Println("time:", time.Since(now))

	now = time.Now()

	fmt.Println("--- generate points in a separate goroutine ---")

	var wg sync.WaitGroup
	wg.Add(1)

	go generateRandomPoints(100000000, &wg)

	wg.Wait()

	fmt.Println("with 100000000 points. PI =", 4.0*(float64(insidePoints)/float64(100000000)))
	fmt.Println("time:", time.Since(now))

	now = time.Now()

	fmt.Println("--- multithreaded execution ---")
	fmt.Println("with 100000000 points. PI =", concurrentEstimatePI(100000000))
	fmt.Println("time:", time.Since(now))

	now = time.Now()

	fmt.Println("--- multithreaded with mutex ---")
	insidePoints = 0

	for i := 0; i < 8; i++ {
		wg.Add(1)
		go generateRandomPointsWithLock(1000000, &wg)
	}

	wg.Wait()
	fmt.Println("with 1000000 points. PI =", 4.0*(float64(insidePoints)/float64(8*1000000)))

	fmt.Println("time:", time.Since(now))

}

func generateRandomPoints(totalPoints int, wg *sync.WaitGroup) {
	for i := 0; i < totalPoints; i++ {
		x := rand.Float64()
		y := rand.Float64()

		if x*x+y*y < 1 {
			insidePoints++
		}
	}
	wg.Done()
}

func generateRandomPointsWithLock(totalPoints int, wg *sync.WaitGroup) {
	for i := 0; i < totalPoints; i++ {
		x := rand.Float64()
		y := rand.Float64()

		if x*x+y*y < 1 {
			lock.Lock()
			insidePoints++
			lock.Unlock()
		}
	}
	wg.Done()
}

func concurrentEstimatePI(totalPoints int) float64 {
	goroutinesNum := runtime.NumCPU()

	goroutinesPoints := totalPoints / goroutinesNum

	results := make(chan float64, goroutinesNum)

	for i := 0; i < goroutinesNum; i++ {
		go func() {
			var in int

			r := rand.New(rand.NewSource(time.Now().UnixNano()))

			for j := 0; j < goroutinesPoints; j++ {
				x := r.Float64()
				y := r.Float64()

				if x*x+y*y < 1 {
					in++
				}
			}

			results <- 4 * (float64(in) / float64(goroutinesPoints))
		}()
	}

	var total float64
	for i := 0; i < goroutinesNum; i++ {
		total += <-results
	}

	return total / float64(goroutinesNum)
}

func serialEstimatePI(totalPoints int) float64 {
	var in int

	for i := 0; i < totalPoints; i++ {
		x := rand.Float64()
		y := rand.Float64()

		if x*x+y*y < 1 {
			in++
		}
	}

	return 4 * (float64(in) / float64(totalPoints))
}
