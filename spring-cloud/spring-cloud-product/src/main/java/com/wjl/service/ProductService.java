package com.wjl.service;

import com.wjl.eneity.Product;
import com.wjl.mapper.ProductMapper;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import org.springframework.web.bind.annotation.PathVariable;

@Service
public class ProductService {
    @Autowired
    private ProductMapper productMapper;

    public String getProductName(Integer id){
        com.wjl.eneity.Product product = productMapper.selectById(id);
        if(product!=null){
            return product.getProductName();
        }
        return null;
    }

    public Integer getPrice(Integer id){
        com.wjl.eneity.Product product = productMapper.selectById(id);
        if(product!=null){
            return product.getPrice();
        }
        return null;
    }
}
