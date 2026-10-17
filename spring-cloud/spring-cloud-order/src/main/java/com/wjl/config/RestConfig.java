package com.wjl.config;

import org.springframework.cloud.client.loadbalancer.LoadBalanced;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;
import org.springframework.web.client.RestTemplate;

@Configuration
public class RestConfig {

    @Bean
    @LoadBalanced //Spring Cloud 内置了 Spring Cloud LoadBalancer
    public RestTemplate restTemplate() {
        return new RestTemplate();
    }
}
