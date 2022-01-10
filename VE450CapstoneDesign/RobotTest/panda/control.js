<script>
$(function(){
    $("button").click(function(){
        $.post("/cmd",this.id,function(data,status){});
        //表示 按钮对应的id值 会被传入树莓派服务器中，就如同 你在树莓派的命令行（cmd）中输入 id 的值
    });
});

</script>
