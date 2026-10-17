package com.wjl.eneity;

import com.baomidou.mybatisplus.annotation.IdType;
import com.baomidou.mybatisplus.annotation.TableId;
import com.baomidou.mybatisplus.annotation.TableName;
import lombok.Data;

@Data
@TableName(value = "tb_product")
public class Product {
    @TableId(value = "id", type = IdType.AUTO)
    private Integer id;
    private String productName;
    private Integer price;
}
