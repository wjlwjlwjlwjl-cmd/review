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
        org.springframework.cloud.client.ServiceInstance instance = discoveryClient.getInstances("cloud-product").get(0);
        String uri = instance.getUri().toString() + "/product/get_product_name?id=1";
        System.out.println(uri);
        System.out.println(restTemplate.getForObject(uri,String.class));
    }
}
