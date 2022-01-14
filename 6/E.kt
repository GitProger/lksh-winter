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

fun List<List<Int>>.toBigInt2DList() = this.map { i -> 
    i.map { it.toBigInteger() } 
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
    override fun toString() = matrix.indices.map { 
        val beg = if (it == 0) "/ " else if (it == h - 1) "\\ " else "| "
        val end = if (it == 0) " \\" else if (it == h - 1) " /" else " |"
        beg + matrix[it].joinToString(" ") + end
    }.joinToString("\n")

    companion object {
        protected fun mul(a: List<BigInt>, b: List<BigInt>) =
            a.indices.sumBy { a[it] * b[it] }
    }
    protected fun mod(a: BigInt) = 
        if (module == -BigInt.ONE) a else (a % module + module) % module
    
    operator fun plus(that: Matrix): Matrix {
        if (this.module != that.module) throw Exception("Different Matrix.module")
        if (this.w != that.w) throw Exception("Different height and width in addition")
        if (this.h != that.h) throw Exception("Different height and width in addition")
        val res = Matrix(this.h, that.w, module)
        for (i in 0 until this.h)
            for (j in 0 until that.w)
                res[i, j] = mod(this[i, j] + that[i, j])
        return res
    }

    operator fun minus(that: Matrix): Matrix {
        if (this.module != that.module) throw Exception("Different Matrix.module")
        if (this.w != that.w) throw Exception("Different height and width in substitution")
        if (this.h != that.h) throw Exception("Different height and width in substitution")
        val res = Matrix(this.h, that.w, module)
        for (i in 0 until this.h)
            for (j in 0 until that.w)
                res[i, j] = mod(this[i, j] - that[i, j])
        return res
    }
    
    operator fun times(that: Matrix): Matrix {
        if (this.module != that.module) throw Exception("Different Matrix.module")
        if (this.w != that.h) throw Exception("Different height and width in multiplication")
        val res = Matrix(this.h, that.w, module)
        for (i in 0 until this.h)
            for (j in 0 until that.w)
                res[i, j] = mod(mul(this.getRow(i), that.getCol(j)))
        return res
    }
    
    operator fun times(c: BigInt) = Matrix(
        (0 until this.h).toList().map { i-> 
            (0 until this.w).toList().map { j -> 
                mod(this[i, j] * c)
            }
        }, 
        module
    )
    
    
    fun pow(x: BigInt): Matrix {
        if (h != w) throw Exception("Power not a square matrix")
        if (x == ZERO) return Matrix(h, w, module).also {
            for (i in 0 until h) it[i, i] = ONE
        }
        val r = this.pow(x / TWO)
        return if (x % TWO == ZERO) r * r else r * r * this
    }
}

open class Vector : Matrix {
    constructor (n: Int, module: BigInt) : super(n, 1, module) {}
    constructor (l: List<BigInt>, mod: BigInt) : super(listOf(l), mod) {}
}





val MOD = 1000000007.toBigInteger()
fun getSolution(a: BigInt, b: BigInt, c: BigInt, d: BigInt, e: BigInt, n: BigInt): BigInt {
    if (n == ONE || n == TWO) return ONE

    val step = Matrix(listOf(
        listOf(a, b, c, d, e).map { it.toInt() },
        listOf(1, 0, 0, 0, 0),
        listOf(0, 0, 2, 0, 0),
        listOf(0, 0, 0, 1, 1),
        listOf(0, 0, 0, 0, 1)
    ).toBigInt2DList(), MOD)
    var first = Matrix(listOf(
       listOf(1),
       listOf(1),
       listOf(8),
       listOf(3),
       listOf(1)
    ).toBigInt2DList(), MOD)

    val ans = step.pow(n - TWO) * first
    return ans[0, 0]
}


public operator fun <T> List<T>.component6(): T {
    return get(5)
}

fun solve() {
    val txt = File("fibonacci.in").readLines().joinToString("")
    val (a, b, c, d, e, n) = txt.trim().split(" ").map { BigInt(it) }
    File("fibonacci.out").writeText(getSolution(a, b, c, d, e, n).toString())//*/
//    val (a, b, c, d, e, n) = readStrings().map { BigInt(it) }
//    println(getSolution(a, b, c, d, e, n).toString())
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

