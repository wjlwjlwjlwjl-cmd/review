package com.wjl.controller;

import com.wjl.service.OrderService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;

@RestController
@RequestMapping("/order")
public class OrderController {
    @Autowired
    private OrderService orderService;

    @RequestMapping("/get_owner_name")
    public String getOwnerName(@RequestParam Integer id) {
        return orderService.getOwnerName(id);
    }

    @RequestMapping("/get_product_id")
    public Long getProductId(@RequestParam Integer id){
        return orderService.getProductId(id);
    }
}
