## @RequestMapping

1. **@RequestMapping** 用来完成方法的路径映射，通过 `method=xxx` 制定请求方法，默认支持 get & post

2. **@RequestParam** 用来解决前后端参数名称不一致导致的参数无法接收的问题，同时默认被该注解修饰的参数为不可省略参数，如需修改，增加 `required=false`

3. 多个同名参数默认是匹配到数组；如果匹配到集合，需要使用 `@RequestParam` 注解；接收 Json 对象时，就需要使用 `@RequestBody` 注解，这时 json 数据就放在请求报文正文中

4. 使用 `@PathVariable` 注解获取路径参数

5. 使用 `@RequestFile` 注解获取文件，搭配 `MultipartFile` 使用，通过 `MultipartFile` 对象提供的 `transferTo` 转换到 `java.io.File`，并对文件进行处理 

6. 获取 Cookie 

  * 通过 `HttpServletResponse` 的 `getCookies` 获得一个 `Cookie` 数组，其中包含了 Cookie 键值对

  * 通过 `@CookieValue("cookieName")` 注解获取，这种方式获取的是部分cookie字段，上面的方法是获取全部的

7. 获取 Session

  * 在 Spring 中，Session 对象是通过 `HttpSession` 来描述的，通过获取请求中的 `SessionId` 来创建或查询 Session，设置、获取属性的方法为 `setAttribute`、`getAttribute`

  * 获取 Session 主要有三种方法

    1. 直接通过 `HttpServletRequest.getSession()` 获取，如果传 false 的话，代表只查询不创建

    2. 通过 `@SessionAttribute("attr-name")` 获取，同时可以通过 `value=xxx, required=xxx` 的方式制定获取字段和是否创建

    3. Spring MVC 内置了 `HttpSession` 对象，可以直接通过其进行创建式的获取

8. 获取 Header

  * Header字段包括各种 HTTP 报头中的请求信息，比如 `User-Agent`、`Cookie`、`Host` 等

  * 获取方式主要两种，一种是通过 `HttpServletRequest.getHeader("name")`，另一种是通过 `@RequestHeader("name")`

9. 设置响应

  * 在 MVC 架构中，Controller 在接受到浏览器的请求后，选择合适的模型处理请求，并接受处理结果，随后挑选合适的视图返回。不过在前后端分离的情况下，返回的视图也有可能是构建视图所需的数据

  * 使用 `@Controller` 注解表示将这个类交给 Spring 作为 Controller 管理，这时默认返回的内容作为视图处理，即会到相应目录寻找所制定的页面，如果没有就会自动返回 404

  * 使用 `@ResponseBody` 表示将返回结果作为非视图内容处理，`Content-Type` 会进行自动识别设置

  * `@ResponseBody` 既是方法注解，又是类注解；`@RestController` 等价于 `@Controller` + `@ResponseBody`，表示当前类是 Controller，同时返回的所有内容都是非视图

10. IoC & DI

  * `IoC` 指的是 `Inversion of Control`，即控制反转，将对象的创建、管理交给第三方处理。在 Spring 这里，就是交给 Spring 管理，需要时，只需要到 Spring 管理的对象中去取即可，所以 Spring 也被叫做 Spring 容器。IoC 降低了使用资源时的耦合度，也方便集中进行资源管理

  * `DI` 指的是依赖注入，`IoC` 更多的指的是一种资源管理思想，而我们的 `DI` 是这种思想的实现方式之一

  * bean 指的是交给 Spring 创建并管理的对象，从 Spring 容器中获取这些对象就是 `getBean`，常用的有三种方法：通过 bean 名称、通过 bean 类型、通过 bean 名称 + 类型

  * `ApplicationContext` 和 `BeanFactory` 的关系

    * 从继承关系来说，`ApplicationContext` 是 `BeanFactory` 的子类

    * 从功能上来说，`BeanFactory` 提供了基础的访问容器的能力，`ApplicationContext` 具有 `BeanFacotry` 的所有功能，同时又添加了比如国际化、事务传播支持、资源访问支持等

    * 从性能上来说，`ApplicationContext` 一次性加载并实例化所有 bean，而 `BeanFactory` 在启动时不实例化任何 bean，而是只加载相应的类的定义信息，用到时再实例化 bean

  * 三种注入方式（思想）及对比

    * 属性注入，直接在属性处使用 `@Autowired` 注解，优点是简洁，缺点：因为 `@Autowired` 是 spring 处理实现的，所以如果不搭配 IoC 容器使用，就等价于没有进行任何处理，相应属性始终未初始化；不能为 final 属性进行初始化；只有在使用时才会报 NullPointerException

    * 构造方法注入，在构造方法处加上 `@Autowired`，优点是支持对 final 属性初始化，同时不需要搭配 IoC 容器使用，构造函数是 JVM 自身支持的语法，依赖对象在使用以前就全部完成了初始化，缺点：依赖对象较多时代码会较为繁琐

    * setter 注入，在 setter 函数上加上 `@Autowired`，优点是能够在类实例化之后，对属性进行注入修改；缺点也在这里，不能注入final属性，不能保证注入对象不被修改

11. Bean 注解

  * 类注解：

    1. `@Controller`，控制器存储，负责接收请求并进行相应

    2. `@Service`，服务器存储，进行对请求的实际业务处理

    3. `@Repository`，仓库存储，与数据库进行交互，即持久化层

    4. `@Component`，组件存储，是元注解，其他注解都是 `@Component` 的“子类”

    5. `@Configuration`，配置存储，包含项目中的配置信息

  * 方法注解 `@Bean`，作用于方法上，表示该方法返回的对象交给 Spring 容器管理，在不方便给类加注解，比如使用第三方库的类时使用；`@Bean(name{"newName", "oldName"})` 可以给类重命名后交给 Spring 管理

12. `@Autowired` 使用时问题  

  * 当一个类存在多个 bean 时，会出现 spring 不知道返回哪个对象的问题，因为 `@Autowired` 是通过类型识别对象的

  * 解决方法：

    * `@Primary`，指定默认使用的 bean

    * `@Qualifier("beanName")`，通过名称区分 bean

    * `@Resource`，通过 bean 的名称区分，不同的是，这是 JDK 提供的注解，不需要像 `@Qualifier` 一样与 `@Autowired` 搭配使用 

13. 拦截器

  * 重写接口 `HandlerInterceptor`，规定拦截前、拦截后、拦截视图渲染完成后的动作

  * 任意类重写 `WebMvcConfigurer`，添加屏蔽器、拦截路径、放行路径

14. 统一返回结果

  * 重写 `ResponseBodyAdvice`，并使用 `@ControllerAdvice` 和 `@ResponseBody` 修饰，这样所有 Controller 返回的方法都会通过统一的结构返回，不过需要注意的是不能直接返回 `String` 这样的类，需要格式化为 Json 这样的字符串，并设置返回类型为 `json/application`，或者直接返回统一的返回结果，不走统一过程

15. 统一异常处理

  * 直接使用上面的统一返回结果的话，即使发生内部错误，产生了异常，也会进行正确结果的格式化流程，所以需要统一异常处理

  * 依然需要使用类注解 `@ControllerAdvice`，但是不再需要继承某个类，在内部实现方法注解 `@ExceptionHandler` 修饰的处理方法即可，并可以在参数中接受不同类型的异常（或者在 `@ExceptionHandler` 中指定类型），返回相应信息（类似与 catch 的思想）

16. Spring AOP

  * AOP 指的是 Aspect Oriented Programing，即面向切面编程

  * 这里的切面，指的是某一类问题，可以理解为面向接口方法编程。比如拦截器、统一接口方法、统一异常处理都含有 AOP 思想

  * Spring AOP 分为几个部分

    * 切点，提供一组规则，描述什么样的方法需要操作；规则通过切点表达式描述

    * 连接点，即符合切点表达式的具体方法

    * 通知，需要重复执行的逻辑，最终体现为一个方法，即通知方法

    * 切面 = 切点 + 通知

  * 通知类型

    * `@Around`，环绕通知，被标记的通知方法在目标方法执行前后都执行

    * `@Before`，通知方法只在目标方法执行前执行

    * `@After`，通知方法在目标方法执行后执行，无论是否抛出异常

    * `@AfterRunning`，通知方法只在目标方法执行后，并且没有异常抛出时执行

    * `@AfterThrowing`，通知方法只在目标方法抛出异常后执行

    实际上 `@Around` 使用的更多，因为它可以通过代码实现出其他通知类型的功能

  * `@PointCut` 注解用来标记一个切点表达式，不需要每个通知方法都写一份。切点定义使用 `private` 时，只能在当前切面使用，，如果定义为 `public`，其他切面可以通过全限定类名 + 方法名的方式使用

  * `@Order(int)` 注解用来指定切面优先级，因为会出现一个方法符合多个切面类的切点表达式的情况，此时为了方便管理就可以指定执行顺序，类似于套壳，目标方法执行前先执行的通知方法，在目标方法执行后后执行

  * 切点表达式

    * `execution([访问修饰符] <返回类型> <包名.类名.方法名(方法参数)> [异常])`，其中访问修饰符、异常都是可以省略的。可以使用的通配符有：

      * `*`，匹配任意一个实体，比如包名、类名、方法名、参数等

      * `..`，表示匹配任意多个任意类型
