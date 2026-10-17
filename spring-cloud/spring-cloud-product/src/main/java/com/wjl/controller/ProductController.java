package com.wjl.controller;

import com.wjl.service.ProductService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;

@RestController
@RequestMapping("/product")
public class ProductController {
    @Autowired
    private ProductService productService;

    @RequestMapping("/get_product_name")
    public String get_product_name(@RequestParam("id") Integer id){
        return productService.getProductName(id);
    }

    @RequestMapping("/get_price")
    public Integer  get_price(@RequestParam("id") Integer id){
        return productService.getPrice(id);
    }
}
