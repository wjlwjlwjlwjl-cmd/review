# ext文件系统
ext2是较早的版本，ext3、ext4均是在ext2的改进，核心设计并没有发生改变。
```cpp
//MBR Partition1 Partition2 Partition3...
//    /        \
// Boot Block   ext2 File System
//               /             \
//    Block Group1   Block Group2...
//                   /          \
//   Super Block   GDT   Block Bitmap   inode Bitmap   inode table   block table 
```
## Boot Block
是一个分区中任何一个文件系统都没有权利修改的分区，存放着系统启动相关信息，一旦破坏，基本上就无法正常启动使用相关分区或者文件系统的操作系如同了
## Block Gruop 块组
ext2文件系统有多个块组组成
## Super Block 超级块
是整个文件系统相关信息的描述，包括block大小、inode大小、已使用和未使用的inode数目、已使用和未使用的block数目、最后一次读写时间等等
可以说，一旦超级块被破坏，这个文件系统就报废了。<br>
所以，文件系统会在第一个块组的开头放置一个超级块的备份（至于其他分区开头是否备份没有硬性要求），以保证在硬盘保存超级块的区域受损后文件系统依然能够正常使用
## GDB 块组描述符表
group desctiption table，描述这个块组的信息，比如inode数目，block bitmap、inode bitmap、inode table、block table的起止位置等等
块组描述符表的数目，与文件系统中块组的数目相同，每个块组的起始位置也会保存一份GDB的拷贝
## 两个bitmap和table
bitmap用来表示相应的table中的相应存储位置是否被占用，真正的内容存储在table中，bitmap起到辅助检索的作用
# 创建一个文件的过程
## 目录和文件的区别
在linux下，两者没有本质区别，目录其实也是存储在文件系统中的文件，或者换句话说，linux中没有目录只有文件。目录在block中存储了
其中包含的所有文件和目录的名称，在inode中保存了文件名和inode的映射关系，这样就可以通过文件名获得inode，从而获得访问目标文件
所需要的信息了
1. 首先查找到空闲的block和inode，存储数据到block，存储文件信息到inode
2. 更新所在目录的inode信息，更新文件名和inode的映射关系
# 软硬连接
## 硬链接
硬链接其实建立的是相同的inode和文件的映射关系，每建立一个硬链接，硬连接数就+1，当文件删除时，先将硬连接数-1
如果减为零，就将文件删除。所以硬链接可以用于文件的备份
## 软连接
软连接是通过名字引用另一个文件，软连接文件和被链接文件是两个文件，类似于桌面快捷方式
