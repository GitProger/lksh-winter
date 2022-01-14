import kotlin.math.*
//import kotlin.text.*
//import kotlin.random.*
import java.math.BigInteger
import java.math.BigDecimal
import java.util.Random
import java.io.File

val PREC = 15
val ZERO = BigDecimal(0.0).setScale(PREC)
val ONE = BigDecimal(1.0).setScale(PREC)
typealias BigDec = BigDecimal
typealias BigInt = BigInteger


fun zero(x: BigDec) = x.abs() < BigDec(1e-10)

fun gauss(a: MutableList<MutableList<BigDec>>): MutableList<BigDec> {
    val n = a.size
    val m = a[0].size - 1
    val x = MutableList<BigDec>(m) { ZERO }
    var r = 0

    for (i in 0 until m) {
        var found = -1;
        for (j in r until n) {
            if (!zero(a[j][i])) {
                found = j
                break
            }
        }
        if (found == -1) continue
        if (zero(a[found][i])) continue
        a[found] = a[r].also { a[r] = a[found] }

        for (j in 0 until n) {
            if (j == r) continue
            val c = a[j][i] / a[r][i]
            for (k in i .. m) {
                a[j][k] -= a[r][k] * c
            }
        }

        r++
        if (r == n) break
    }
    
    if (r < m) {
        for (i in 0 until n) {
            var all_zero = true
            for (j in 0 until m) {
                if (!zero(a[i][j])) {
                    all_zero = false
                }
            }
            if (all_zero && !zero(a[i][m])) {
                throw Exception("No solutions");
            }
        }
        throw Exception("Infinity solutions");
    }
    
    for (i in m - 1 downTo 0) {
        x[i] = a[i][m] / a[i][i]
        for (c in m - 1 downTo i + 1) {
            x[i] -= a[i][c] * x[c] / a[i][i]
        }
    }
    return x
}


fun sum(n: Int, k: Int): BigDec {
    var s = ZERO
    for (i in 1 .. n) {
        s += i.toBigDecimal().pow(k).setScale(PREC)
    }
    return s
}

fun solve() {
    val k = readInt()
    val a = mutableListOf<MutableList<BigDec>>();    

    for (n in 1 .. k + 1) {
        a.add((List(k + 1) { i ->
            n.toBigDecimal().pow(i + 1).setScale(PREC)
        } + listOf(sum(n, k))).toMutableList());
    }
    println(gauss(a).map { it.setScale(6) }.joinToString(" "))
    
}


const val MULTITEST = false
fun main(args: Array<String>) {
    repeat (if (MULTITEST) readInt() else 1) {
        solve()
    }
}
private fun readln() = readLine()!!
private fun readInt() = readln().toInt()
//private fun readStrings() = readln().trim().split("\\s+".toRegex())
private fun readStrings() = readln().trim().split(" ")
private fun readInts() = readStrings().map { it.toInt() }
private infix fun Int.to(to: Int) = if (to > this) this..to else this downTo to
fun Boolean.toInt() = if (this == true) 1 else 0

