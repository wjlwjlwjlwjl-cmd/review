## @RequestMapping

1. **@RequestMapping** 用来完成方法的路径映射，通过 `method=xxx` 制定请求方法，默认支持 get & post

2. **@RequestParam** 用来解决前后端参数名称不一致导致的参数无法接收的问题，同时默认被该注解修饰的参数为不可省略参数，如需修改，增加 `required=false`

3. 多个同名参数默认是匹配到数组；如果匹配到集合，需要使用 `@RequestParam` 注解；接收 Json 对象时，就需要使用 `@RequestBody` 注解，这时 json 数据就放在请求报文正文中

4. 使用 `@PathVariable` 注解获取路径参数

5. 使用 `@RequestFile` 注解获取文件，搭配 `MultipartFile` 使用，通过 `MultipartFile` 对象提供的 `transferTo` 转换到 `java.io.File`，并对文件进行处理 

6. 获取 Cookie 

  * 通过 `HttpServletResponse` 的 `getCookies` 获得一个 `Cookie` 数组，其中包含了 Cookie 键值对

  * 通过 `@CookieValue("cookieName")` 注解获取，这种方式获取的是部分cookie字段，上面的方法是获取全部的
