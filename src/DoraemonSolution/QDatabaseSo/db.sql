INSERT INTO `doraemon_config`
(`id`,`keyName`,`keyValue`)
VALUES(1, 'classSyncTime','0');

INSERT INTO `doraemon_config`
(`id`,`keyName`,`keyValue`)
VALUES(2, 'resourceServer','http://www.firemail.wang:8088');


INSERT INTO `classification`
(`classId`,`cnName`,`enName`,`parentId`,`status`,`sortNum`,`des`)
VALUES(1, '春晖学府','chunhui',0,0,0,'chunhuitech.cn');

INSERT INTO `classification`
(`classId`,`cnName`,`enName`,`parentId`,`status`,`sortNum`,`des`)
VALUES(2, '幼教','preschool',1,0,0,'Preschool education');

INSERT INTO `classification`
(`classId`,`cnName`,`enName`,`parentId`,`status`,`sortNum`,`des`)
VALUES(3, '汉语拼音','pinyin',2,0,0,'普通话中共有39个韵母,23个声母,16个整体认读音节');

INSERT INTO `classification`
(`classId`,`cnName`,`enName`,`parentId`,`status`,`sortNum`,`des`)
VALUES(4, '汉字','hanzi',2,0,0,'2500个汉字');

INSERT INTO `classification`
(`classId`,`cnName`,`enName`,`parentId`,`status`,`sortNum`,`des`)
VALUES(5, '26个英文字母','letters',2,0,0,'26个英文字母发音、笔画');


INSERT INTO `record`
(`recordId`,`classId`,`sortNum`,`title`,`label`,`relativePath`,`fileSize`,`fileType`,`contentHtml`,`contentPlain`,`status`,`modifyTime`,`createTime`)
VALUES(1, 5,0,'a','A','/chunhui_resource/preschool/letters/a.swf',45000,'SWF','','',0,1519297787,1519297787);

INSERT INTO `record`
(`recordId`,`classId`,`sortNum`,`title`,`label`,`relativePath`,`fileSize`,`fileType`,`contentHtml`,`contentPlain`,`status`,`modifyTime`,`createTime`)
VALUES(2, 5,0,'b','B','/chunhui_resource/preschool/letters/b.swf',45000,'SWF','','',0,1519297787,1519297787);

INSERT INTO `record`
(`recordId`,`classId`,`sortNum`,`title`,`label`,`relativePath`,`fileSize`,`fileType`,`contentHtml`,`contentPlain`,`status`,`modifyTime`,`createTime`)
VALUES(3, 5,0,'c','C','/chunhui_resource/preschool/letters/c.swf',45000,'SWF','','',0,1519297787,1519297787);
