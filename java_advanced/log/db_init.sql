-- 建表SQL
create database if not exists java_blog_spring charset utf8mb4;
use java_blog_spring;
-- 用户表
DROP TABLE IF EXISTS java_blog_spring.user_info;
CREATE TABLE java_blog_spring.user_info(
`id` INT NOT NULL AUTO_INCREMENT,
`user_name` VARCHAR ( 128 ) NOT NULL,
`password` VARCHAR ( 128 ) NOT NULL,
`github_url` VARCHAR ( 128 ) NULL,
`delete_flag` TINYINT ( 4 ) NULL DEFAULT 0,
`create_time` DATETIME DEFAULT now(),
`update_time` DATETIME DEFAULT now() ON UPDATE now(),
PRIMARY KEY ( id ),
UNIQUE INDEX user_name_UNIQUE ( user_name ASC )) ENGINE = INNODB DEFAULT
CHARACTER
SET = utf8mb4 COMMENT = '用户表';
-- 博客表
drop table if exists java_blog_spring.blog_info;
CREATE TABLE java_blog_spring.blog_info (
`id` INT NOT NULL AUTO_INCREMENT,
`title` VARCHAR(200) NULL,
`content` TEXT NULL,
`user_id` INT(11) NULL,
`delete_flag` TINYINT(4) NULL DEFAULT 0,
`create_time` DATETIME DEFAULT now(),
`update_time` DATETIME DEFAULT now() ON UPDATE now(),
PRIMARY KEY (id))
ENGINE = InnoDB DEFAULT CHARSET = utf8mb4 COMMENT = '博客表';
-- 新增用户信息
insert into java_blog_spring.user_info (user_name,
password,github_url)values("zhangsan","123456","https://gitee.com/bubblefish666/class-java45");
insert into java_blog_spring.user_info (user_name,
password,github_url)values("lisi","123456","https://gitee.com/bubblefish666/class-java45");
insert into java_blog_spring.blog_info (title,content,user_id) values("第一篇博客","111我是博客正文我是博客正文我是博客正文",1);
insert into java_blog_spring.blog_info (title,content,user_id) values("第二篇博客","222我是博客正文我是博客正文我是博客正文",2);