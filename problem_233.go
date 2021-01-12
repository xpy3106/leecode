/*
 * leecode problem 233: Number of Digit One
 */
func countDigitOne(n int) int {
    if n < 0 {
        return 0
    }
    cnt := 0
	for m := 1; m <= n; m *= 10 {
		a := n / m
		b := n % m
		switch a % 10 {
        case 0:
            cnt += (a/10) * m
		case 1:
			cnt += (a/10 ) * m  + (b + 1)
		default:
            cnt += (a/10 + 1) * m
		}
	}

	return cnt
}
