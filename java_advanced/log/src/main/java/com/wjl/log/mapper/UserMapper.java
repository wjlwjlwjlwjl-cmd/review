package com.wjl.log.mapper;

import com.baomidou.mybatisplus.core.mapper.BaseMapper;
import com.wjl.log.entity.UserInfo;
import org.apache.ibatis.annotations.Mapper;

@Mapper
public interface UserMapper extends BaseMapper<UserInfo> {
}
