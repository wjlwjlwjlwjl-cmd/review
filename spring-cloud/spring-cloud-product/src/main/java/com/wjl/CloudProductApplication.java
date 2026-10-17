package com.wjl;

import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;

@SpringBootApplication
public class CloudProductApplication {
    public static void main(String[] args) {
        SpringApplication.run(CloudProductApplication.class, args);
        System.out.println("商品服务启动成功");
    }
}
