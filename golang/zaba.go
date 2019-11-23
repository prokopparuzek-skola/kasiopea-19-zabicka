package main

import "fmt"

func comp(kameny []uint, task chan uint) {
	println("OK!")
	N := uint(len(kameny))
	graph := make([]uint, N)
	pA := make([]uint, N)
	pF := make([]uint, N)
	var iA, iF uint
	var test bool = false
	iA = 1
	for i := uint(0); ; i++ {
	cyklus:
		for j := uint(0); j < iA; j++ {
			for k := uint(1); k <= kameny[pA[j]]; k++ {
				if pA[j]+k == N {
					println("OK")
					test = true
					i++
					break cyklus
				}
				if graph[pA[j]+k] == 0 || graph[pA[j]+k] > i+1 {
					graph[pA[j]+k] = i + 1
					pF[iF] = pA[j] + k
					iF++
				}
			}
		}
		if test {
			task <- i
			break
		}
		swp := pA
		pA = pF
		pF = swp
		iA = iF
		iF = 0
	}
}
func main() {
	var T uint
	fmt.Scanf("%d", &T)
	result := make([]chan uint, T)
	for i := 0; i < int(T); i++ {
		result[i] = make(chan uint)
	}
	for i := uint(0); i < T; i++ {
		var N uint
		fmt.Scanf("%d", &N)
		kameny := make([]uint, N)
		for j := uint(0); j < N; j++ {
			fmt.Scanf(" %d", &kameny[j])
		}
		println("Run!")
		go comp(kameny, result[i])
	}
	for i := uint(0); i < T; i++ {
		fmt.Printf("%d\n", <-result[i])
	}
}
