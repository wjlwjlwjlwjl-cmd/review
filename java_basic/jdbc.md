* jdbc 的使用主要分为以下步骤

  1. 获取链接，一种方式是通过 `DriverManager`，制定数据库连接 URL 和用户名、密码；另一种方式是通过池化技术，使用 `mysqlDataSource`，配置过 url、user、password 后，可以作为连接池随时获取链接

  2. 构造sql语句，一种方式是直接通过 `Connection` 获取到普通的 `Statement`，后续直接使用字符串拼接的方式构造sql语句，供给 `Statement` 执行，但是这种方式不仅麻烦，而且无法解决 sql 注入的问题；另一种方式是，使用预编译的sql语句，通过 `Connection` 获取 `preparedStatement`，用 `?` 代表字段占位符，后续填充内容使用 `setType` 的方式，同时下标从1开始，指示填充的位置

  3. 进行查询并获取结果，如果是 select 的话，可以使用 `ResultSet` 接收 `executeQuery` 的返回结果，并通过 `while(resultSet.next()){String name = resultSet.getString(1)}` 获取结果。这里结果通过类型 + 字段在 select 中的序号区分，或者说只通过后者，序号依然是从1开始；如果是 insert 的话，可以使用 `executeUpdate()` 来看受影响的行数，如果是 1 就代表插入成功

  4. 关闭使用到的各种资源，比如 `ResultSet`、`Statement`、`PreparedStatement`、`Connection`
