package com.wjl.entity;

import com.baomidou.mybatisplus.annotation.IdType;
import com.baomidou.mybatisplus.annotation.TableId;
import com.baomidou.mybatisplus.annotation.TableName;
import lombok.Data;

@Data
@TableName(value = "tb_order")
public class Order {
    @TableId(value = "id", type = IdType.AUTO)
    private Long id;
    private String ownerName;
    private Long productId;
}
