package com.wjl;

import jakarta.annotation.Resource;
import org.junit.jupiter.api.Test;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.context.SpringBootTest;
import org.springframework.cloud.client.ServiceInstance;
import org.springframework.cloud.client.discovery.DiscoveryClient;
import org.springframework.web.client.RestTemplate;

@SpringBootTest
public class CommunicationTest {
    @Autowired
    private RestTemplate restTemplate;
    @Resource
    private DiscoveryClient discoveryClient;

    @Test
    public void test(){
        //调用 cloud-product
        String uri = "http://cloud-product/product/get_product_name?id=1";
        System.out.println(restTemplate.getForObject(uri,String.class));
        System.out.println(restTemplate.getForObject(uri,String.class));
        System.out.println(restTemplate.getForObject(uri,String.class));
        System.out.println(restTemplate.getForObject(uri,String.class));
        System.out.println(restTemplate.getForObject(uri,String.class));
        System.out.println(restTemplate.getForObject(uri,String.class));
        System.out.println(restTemplate.getForObject(uri,String.class));
    }
}
