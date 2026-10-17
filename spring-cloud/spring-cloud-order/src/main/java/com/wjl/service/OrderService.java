package com.wjl.service;

import com.wjl.entity.Order;
import com.wjl.mapper.OrderMapper;
import org.apache.ibatis.annotations.Mapper;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

@Service
public class OrderService {
    @Autowired
    private OrderMapper orderMapper;

    public String getOwnerName(Integer id) {
        Order order = orderMapper.selectById(id);
        if(order!=null){
            return order.getOwnerName();
        }
        return null;
    }

    public Long getProductId(Integer id) {
        Order order = orderMapper.selectById(id);
        if(order!=null){
            return order.getProductId();
        }
        return null;
    }
}
