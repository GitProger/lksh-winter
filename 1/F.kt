import kotlin.math.*
//import kotlin.text.*
//import kotlin.random.*
import java.math.BigInteger
import java.util.Random
import java.io.File

val ZERO = BigInteger.ZERO
val ONE = BigInteger.ONE
val TWO = BigInteger("2")


infix fun BigInteger.mod(b: BigInteger): BigInteger {
    return ((this % b) + b) % b
}
infix fun BigInteger.mod(b: Int): BigInteger {
    val p = b.toBigInteger()
    return ((this % p) + p) % p
}
fun eq(a: BigInteger, b: BigInteger, p: BigInteger) = a mod p == b mod p

fun fpow(a: BigInteger, x: BigInteger, p: BigInteger): BigInteger {
    if (x == ZERO) return ONE
    val r = fpow(a, x / TWO, p) % p
    return if (x mod 2 == ZERO) {
        (r * r) % p
    } else {
        (((r * r) % p) * a) % p
    }
}


fun rand(l: BigInteger, r: BigInteger): BigInteger {
    val rnd = Random().nextLong().toBigInteger()
    return l + rnd % (r - l + ONE)
}

fun rev(a: BigInteger, m: BigInteger) = a.modInverse(m)

fun isPrime(x: BigInteger): Boolean {
    return x.isProbablePrime(20)
}

fun root4(x: BigInteger): BigInteger {
    return ceil(sqrt(sqrt(x.toLong().toDouble())))
        .toLong().toBigInteger()
}

fun Pollard(n: BigInteger): List<BigInteger> {
    fun f(x: BigInteger) = (x * x + ONE) mod n
    if (isPrime(n)) return listOf(n)
    
    var x = rand(TWO, n - ONE)
    val k = root4(n)
    for (i in 0 .. k.toInt()) x = f(x)
    var y = f(x)
    for (i in 0 until k.toInt()) {
        val g = (x - y).abs().gcd(n)
        if (g != ONE)// && g != n)
            return listOf(g) + Pollard(n / g)
        x = y
        y = f(y)
    }
    return listOf<BigInteger>(n)
}
// -----------------------------------------------------------------------------

fun simpleMuls(x: BigInteger): List<BigInteger> {
    var m = x
    val res = mutableListOf<BigInteger>()
    var i = TWO
    while (i * i <= x) {
        while (m % i == ZERO) {
            m = m / i
            res.add(i)
        }
        i = i + ONE
    }
    if (m > ONE) res.add(m)
    return res.toList()
}

fun optimize(m: List<BigInteger>): List<BigInteger> {
    return m.flatMap {
        if (it < 10000.toBigInteger()) {
            simpleMuls(it)
        } else {
            listOf(it)
        }
    }
}


fun solve() {
    val txt = File("pollard.in").readLines().joinToString("")//readln()
    val n = BigInteger(txt)
    File("pollard.out").writeText(
        optimize(Pollard(n))
        .sorted().joinToString(" ")
    )
}


const val MULTITEST = false
fun main() {
    
    repeat (if (MULTITEST) readInt() else 1) {
        solve()
    }
}
private fun readln() = readLine()!!
private fun readInt() = readln().toInt()
//private fun readStrings() = readln().trim().split("\\s+".toRegex())
//private fun readInts() = readStrings().map { it.toInt() }
private infix fun Int.to(to: Int) = if (to > this) this..to else this downTo to
fun Boolean.toInt() = if (this == true) 1 else 0
/*
*/
/*
fun unpack(m: List<BigInteger>): List<BigInteger> {
    val d = MutableList(40000) {true}
    for (i in 2 until d.size)
        for (j in 2 until d.size) {
            if (i * j >= d.size) break
            d[i * j] = false
        }
    val primes = (2 until d.size).toList().filter { d[it] }
        .map { it.toBigInteger() }

    return m.filter { it != ONE }.flatMap { mul ->
        if (isPrime(mul)) 
            listOf(mul) 
        else {
            var res = listOf<BigInteger>()
            for (p in primes) {
                val cnt = log(mul.toBigDecimal().toDouble(), p.toBigDecimal().toDouble())
                if (abs( cnt % 1.0 ) < 1e-9 ) {
                    res = List(cnt.toInt()) {p}
                    break
                }
            }
            if (res.isEmpty()) listOf(mul) else res
        }
    }
}
*/cppquiz
