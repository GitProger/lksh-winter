import kotlin.math.*
//import kotlin.text.*
//import kotlin.random.*
import java.math.BigInteger
import java.util.Random
import java.io.File

val ZERO = BigInteger.ZERO
val ONE = BigInteger.ONE
val TWO = BigInteger("2")
typealias BigInt = BigInteger

inline fun <T> Iterable<T>.sumBy(selector: (T) -> BigInt): BigInt {
    var sum = BigInt.ZERO
    for (element in this) {
        sum += selector(element)
    }
    return sum
}

open class Matrix(private val h: Int,
                  private val w: Int,
                  public val module: BigInt = -BigInt.ONE)
{
    val height: Int get() = h
    val size: Int get() = h
    val width: Int get() = w

    val matrix = MutableList(h) { MutableList(w) { ZERO } }
    constructor(mtx: List<List<BigInt>>, mod: BigInt) : 
        this(mtx.size, mtx[0].size, mod) 
    {
        for (i in 0 until h)
            for (j in 0 until w)
                matrix[i][j] = mtx[i][j]
    }

    fun getRow(i: Int) = matrix[i].toList()
    fun getCol(i: Int) = (0 until h).toList().map { matrix[it][i] }
    operator fun get(i: Int) = matrix[i]
    operator fun get(i: Int, j: Int) = matrix[i][j]
    operator fun set(i: Int, v : MutableList<BigInt>) { matrix[i] = v }
    operator fun set(i: Int, j: Int, v: BigInt) { matrix[i][j] = v }
    override fun toString() = matrix.map { it.joinToString(" ") }.joinToString("\n")
 
    companion object {
        protected fun mul(a: List<BigInt>, b: List<BigInt>) =
            a.indices.sumBy { a[it] * b[it] }
    }
    protected fun mod(a: BigInt) = 
        if (module == -BigInt.ONE) a else (a % module + module) % module
    
    operator fun times(that: Matrix): Matrix {
        if (this.module != that.module) throw Exception("Different Matrix.module")
        if (this.w != that.h) throw Exception("Different height and width in multiplication")
        val res = Matrix(this.h, that.w, module)
        for (i in 0 until this.h)
            for (j in 0 until that.w)
                res[i, j] = mod(mul(this.getRow(i), that.getCol(j)))
        return res
    }
    
    fun pow(x: BigInt): Matrix {
        if (h != w) throw Exception("Power not a square matrix")
        if (x == ZERO) return Matrix(h, w, module).also {
            for (i in 0 until h) it[i, i] = ONE
        }
        val r = this.pow(x / TWO)
        return if (x % TWO == ZERO) r * r else r * r * this
    }
}

fun bit(m: Int, i: Int) = m and (1 shl i) == 0
fun haveSq(m1: Int, m2: Int, ln: Int): Boolean {
    for (i in 1 until ln) {
        if (!bit(m1, i - 1) && !bit(m1, i) && !bit(m2, i - 1) && !bit(m2, i)) return true
        if (bit(m1, i - 1) && bit(m1, i) && bit(m2, i - 1) && bit(m2, i)) return true
    }
    return false    
}

fun getSolution(h: BigInt, w: BigInt, p: BigInt): BigInt {
    val n = 1 shl h.toInt()
    val okTable = List(n) { mask1 ->
        List(n) { mask2 ->
            val v = !haveSq(mask1, mask2, h.toInt())
            if (v) ONE else ZERO
        }
    }
    
    val first = Matrix(List(n) { listOf(ONE) }, p)
    val dp = Matrix(okTable, p).pow(w - ONE) * first

    var sum = ZERO
    for (mask in 0 until n) 
        sum = (sum + dp[mask][0]).mod(p)
    return sum
}


// n-height, m-width

fun solve() {
    val txt = File("nice3.in").readLines().joinToString("")//readln()
    val (m, n, p) = txt.trim().split(" ").map { BigInt(it) }
    File("nice3.out").writeText(getSolution(n, m, p).toString())
 //   val (m, n, p) = readStrings().map { BigInt(it) }
 //   println(getSolution(n, m, p).toString())
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

