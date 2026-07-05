## 一、基本 SQL 编写

MyBatis 的 SQL 编写主要有两种形式，一种是直接通过注解（比如 `@select`、`@insert`、`@update` 等），另一种是通过 XML 文件编写。

两者其实思想上是一样的，只不过把 SQL 模板的位置进行了区分，接口的定义都是一样的，前者是放在注解中，后者是放在 XML 中，理论上来说后者更加清晰一些

另外一个就是 `#{}` 是通过预编译的方式，拼接出 sql，并且会对数据库会进行 SQL 缓存；`${}` 是直接通过字符串拼接得到 sql，除非涉及到 sql 语句本身的结构作为参数，比如升降序、多表联查的表名这类参数，否则不建议使用 `${}`，因为存在 sql 注入 

## 二、动态 SQL

前面讲的基本 sql 编写，基本上只是把 sql 中的数据作为参数，而动态 sql 则是允许把 sql 的结构（比如表名、字段）自动对参数的情况进行适应作为参数，构造出符合传参情况的 sql，从这种角度来看，XML 要更方便一些

### 2.1 <if></if>

`<if></if>` 是允许根据 `test=""` 制定的条件来决定是否添加条件

### 2.2 <trim></trim>

`<trim></trim>` 是为了给 `<if></if>` 标签修饰结构，比如 `insert into table_name values(val1, val2, val3)` 这里的 `,` 就是一个无法直接确定的，所以 `<trim></trim>` 通过 `prefix`、`suffix`、`prefixOverrides`、`suffixOverrides` 这些参数来格式化 sql 结构

### 2.3 <set></set>

`<set></set>` 与 update 操作结合使用，直接俱备 `<trim><trim>` 剔除额外符号的功能

### 3.4 <forEach></forEach>

`<forEach></forEach>` 用来对 sql 语句中的集合进行处理，比如 `where id in (1, 2, 3)` 这种。字段有

  * `collection` 指定参数中的集合对象，比如 List、Set、Map

  * `item` 指定参数中的单个对象，用来在 `foreach` 标签中指定单个对象

  * `open` 在开头加上的符号

  * `close` 在结尾加上的符号

  * `separator` 分隔符

### 3.5 <sql></sql> 和 <include></include>

前者用来定义一个 sql 片段，也可以包含其他 xml 标签，这样重复使用的冗长字段就可以通过后者引用了（前者通过 `id` 标识，后者通过 `refid` 指定引用的 sql 片段
