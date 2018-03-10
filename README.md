# 图片处理

## 一、图片叠加

主要用于两张图片叠加，可以设置一种颜色值作为前景图片的透明色，这样进行叠加时就会忽略这种颜色。

<table>
<tr>
    <td align="center">
        背景图片：<br>
        <img src="http://store.cnzhujie.cn/github/pictureprocess/back.bmp" width="400">
    </td>
    <td>
        前景图片：
        <img src="http://store.cnzhujie.cn/github/pictureprocess/front.bmp" width="400">
    </td>
</tr>
</table>

设定透明色为`#000`，则合成的图片如下所示：

<img src="http://store.cnzhujie.cn/github/pictureprocess/overlap.bmp" width="400">

## 二、图片翻转

1.可以将图片进行左右，上下或者中心翻转

<table>
<tr>
    <td align="center">
        原图<br>
        <img src="http://store.cnzhujie.cn/github/pictureprocess/source.bmp" width="210">
    </td>
    <td align="center">
        左右翻转<br>
        <img src="http://store.cnzhujie.cn/github/pictureprocess/flip_LR.bmp" width="210">
    </td>
    <td align="center">
        上下翻转<br>
        <img src="http://store.cnzhujie.cn/github/pictureprocess/flip_TD.bmp" width="210">
    </td>
    <td align="center">
        中心翻转<br>
        <img src="http://store.cnzhujie.cn/github/pictureprocess/flip_CENTER.bmp" width="210">
    </td>
</tr>
</table>

2.将图片按照中心任意角度翻转（图像边缘可能会发生锯齿状失真）

<table>
<tr>
    <td align="center" width="210">
        原图<br>
        <img src="http://store.cnzhujie.cn/github/pictureprocess/source.bmp" width="210">
    </td>
    <td align="center" width="293">
        逆时针20°<br>
        <img src="http://store.cnzhujie.cn/github/pictureprocess/flip_ANGLE_20.bmp" width="293">
    </td>
    <td align="center" width="280">
        逆时针90°<br>
        <img src="http://store.cnzhujie.cn/github/pictureprocess/flip_ANGLE_90.bmp" width="280">
    </td>
</tr>
</table>
    
<table>
<tr>
    <td align="center">
        逆时针135°<br>
        <img src="http://store.cnzhujie.cn/github/pictureprocess/flip_ANGLE_135.bmp" width="346">
    </td>
    <td align="center">
        逆时针180°<br>
        <img src="http://store.cnzhujie.cn/github/pictureprocess/flip_ANGLE_180.bmp" width="210">
    </td>
    <td align="center">
        逆时针280°<br>
        <img src="http://store.cnzhujie.cn/github/pictureprocess/flip_ANGLE_280.bmp" width="312">
    </td>
</tr>
</table>

## 三、颜色替换

1.替换指定颜色

<table>
<tr>
    <td align="center">
        原图<br>
        <img src="http://store.cnzhujie.cn/github/pictureprocess/front.bmp" width="400">
    </td>
    <td align="center">
        #000 -> #fff<br>
        <img src="http://store.cnzhujie.cn/github/pictureprocess/blackToWhite.bmp" width="400">
    </td>
</tr>
</table>

2.自定义替换规则，例如将彩色图片转化为灰度图片

<table>
<tr>
    <td align="center">
        原图<br>
        <img src="http://store.cnzhujie.cn/github/pictureprocess/source.bmp" width="220">
    </td>
    <td align="center">
        按照彩色转灰度的规则进行替换图像<br>
        <img src="http://store.cnzhujie.cn/github/pictureprocess/gray.bmp" width="220">
    </td>
</tr>
</table>

## 四、图像单色化

<table>
<tr>
    <td align="center">
        原图<br>
        <img src="http://store.cnzhujie.cn/github/pictureprocess/source.bmp" width="210">
    </td>
    <td align="center">
        (r,g,b)->(r,r,r)<br>
        <img src="http://store.cnzhujie.cn/github/pictureprocess/singleColor_r.bmp" width="210">
    </td>
    <td align="center">
        (r,g,b)->(g,g,g)<br>
        <img src="http://store.cnzhujie.cn/github/pictureprocess/singleColor_g.bmp" width="210">
    </td>
    <td align="center">
        (r,g,b)->(b,b,b)<br>
        <img src="http://store.cnzhujie.cn/github/pictureprocess/singleColor_b.bmp" width="210">
    </td>
</tr>
</table>

## 五、反色

将图片的颜色逆反
<table>
<tr>
    <td align="center">
        原图<br>
        <img src="http://store.cnzhujie.cn/github/pictureprocess/source.bmp" width="220">
    </td>
    <td align="center">
        反色图像<br>
        <img src="http://store.cnzhujie.cn/github/pictureprocess/inverseColor.bmp" width="220">
    </td>
</tr>
</table>

## 六、图像平滑处理（模糊处理）

<table>
<tr>
    <td align="center">
        原图<br>
        <img src="http://store.cnzhujie.cn/github/pictureprocess/brightness.bmp" width="220">
    </td>
    <td align="center">
        平滑图像<br>
        <img src="http://store.cnzhujie.cn/github/pictureprocess/smooth.bmp" width="220">
    </td>
</tr>
</table>

## 七、霓虹处理
<table>
    <thead>
            <tr><th>原图</th><th>霓虹图片</th><tr>
    </thead>
    <tbody>
    <tr>
        <td align="center">
            <br/>
            <img src="http://store.cnzhujie.cn/github/pictureprocess/source.bmp" width="220">
        </td>
        <td align="center">
            <br/>
            <img src="http://store.cnzhujie.cn/github/pictureprocess/source_neon.bmp" width="220">
        </td>
    </tr>
    <tr>
        <td align="center">
            <br/>
            <img src="http://store.cnzhujie.cn/github/pictureprocess/front.bmp" width="220">
        </td>
        <td align="center">
            <br/>
            <img src="http://store.cnzhujie.cn/github/pictureprocess/front_neon.bmp" width="220">
        </td>
    </tr>
    <tr>
        <td align="center">
            <br/>
            <img src="http://store.cnzhujie.cn/github/pictureprocess/brightness.bmp" width="220">
        </td>
        <td align="center">
            <br/>
            <img src="http://store.cnzhujie.cn/github/pictureprocess/brightness_neon.bmp" width="220">
        </td>
    </tr>
    </tbody>
</table>

## 八、二值化
<table>
<thead>
	<tr><th>原图</th><th>OTSU</th><th>自定义阈值</th><tr>
</thead>
<tbody>
<tr>
<td align="center">
<br/>
<img src="http://store.cnzhujie.cn/github/pictureprocess/source.bmp" width="220">
</td>
<td align="center">
<br/>
<img src="http://store.cnzhujie.cn/github/pictureprocess/source_otsn.bmp" width="220">
</td>
<td align="center">
阈值：128<br/>
<img src="http://store.cnzhujie.cn/github/pictureprocess/source_binaryzation.bmp" width="220">
</td>
</tr>
<tr>
<td align="center">
<br/>
<img src="http://store.cnzhujie.cn/github/pictureprocess/front.bmp" width="220">
</td>
<td align="center">
<br/>
<img src="http://store.cnzhujie.cn/github/pictureprocess/front_otsn.bmp" width="220">
</td>
<td align="center">
阈值：10<br/>
<img src="http://store.cnzhujie.cn/github/pictureprocess/front_binaryzation.bmp" width="220">
</td>
</tr>
<tr>
<td align="center">
<br/>
<img src="http://store.cnzhujie.cn/github/pictureprocess/brightness.bmp" width="220">
</td>
<td align="center">
<br/>
<img src="http://store.cnzhujie.cn/github/pictureprocess/brightness_otsn.bmp" width="220">
</td>
<td align="center">
阈值：128<br/>
<img src="http://store.cnzhujie.cn/github/pictureprocess/brightness_binaryzation.bmp" width="220">
</td>
</tr>
</tbody></table>

## 九、亮度调节
1.按YUV成比例调节亮度
<table><tr>
<td align="center">
原图<br>
<img src="http://store.cnzhujie.cn/github/pictureprocess/brightness.bmp" width="220">
</td>
<td align="center">
原图亮度的120%<br>
<img src="http://store.cnzhujie.cn/github/pictureprocess/scalelight.bmp" width="220">
</td>
<td align="center">
原图亮度的50%<br>
<img src="http://store.cnzhujie.cn/github/pictureprocess/scaledark.bmp" width="220">
</td>
</tr></table>
2.按像素值调节亮度
<table><tr>
<td align="center">
原图<br>
<img src="http://store.cnzhujie.cn/github/pictureprocess/brightness.bmp" width="220">
</td>
<td align="center">
原图像素值加30<br>
<img src="http://store.cnzhujie.cn/github/pictureprocess/steplight.bmp" width="220">
</td>
<td align="center">
原图像素值减30<br>
<img src="http://store.cnzhujie.cn/github/pictureprocess/stepdark.bmp" width="220">
</td>
</tr></table>

## 十、色调调节

<table><tr>
<td align="center">
原图<br>
<img src="http://store.cnzhujie.cn/github/pictureprocess/brightness.bmp" width="210">
</td>
<td align="center">
(r,g,b)->(r-10,g-20,b+30)<br>
<img src="http://store.cnzhujie.cn/github/pictureprocess/tuneHue_30_-20_-10.bmp" width="210">
</td>
<td align="center">
(r,g,b)->(r+10,g+20,b-30)<br>
<img src="http://store.cnzhujie.cn/github/pictureprocess/tuneHue_-30_20_10.bmp" width="210">
</td>
<td align="center">
(r,g,b)->(r+10,g-20,b+30)<br>
<img src="http://store.cnzhujie.cn/github/pictureprocess/tuneHue_30_-20_10.bmp" width="210">
</td>
</tr></table>

## 十一、图像缩放

1.临近插值法（图像会失真）
<table><tr>
<td align="center">
原图<br>
<img src="http://store.cnzhujie.cn/github/pictureprocess/brightness.bmp" width="220">
</td>
<td align="center">
80%<br>
<img src="http://store.cnzhujie.cn/github/pictureprocess/zoomTo0.8.bmp" width="176">
</td>
<td align="center">
180%<br>
<img src="http://store.cnzhujie.cn/github/pictureprocess/zoomTo1.8.bmp" width="396">
</td>
</tr></table>

2.双线性内插值（失真度小）
<table><tr>
<td align="center">
原图<br>
<img src="http://store.cnzhujie.cn/github/pictureprocess/brightness.bmp" width="220">
</td>
<td align="center">
80%<br>
<img src="http://store.cnzhujie.cn/github/pictureprocess/zoomToLinear0.8.bmp" width="176">
</td>
<td align="center">
180%<br>
<img src="http://store.cnzhujie.cn/github/pictureprocess/zoomToLinear1.8.bmp" width="396">
</td>
</tr></table>

## 十二、图像循环移位
<table><tr>
<td align="center">
原图<br>
<img src="http://store.cnzhujie.cn/github/pictureprocess/source.bmp" width="210">
</td>
<td align="center">
下移100像素<br>
<img src="http://store.cnzhujie.cn/github/pictureprocess/circularShift_0_-100.bmp" width="210">
</td>
<td align="center">
右移100像素<br>
<img src="http://store.cnzhujie.cn/github/pictureprocess/circularShift_100_0.bmp" width="210">
</td>
<td align="center">
下移100像素,右移100像素<br>
<img src="http://store.cnzhujie.cn/github/pictureprocess/circularShift_100_-100.bmp" width="210">
</td>
</tr></table>


## 参考网址：

http://blog.csdn.net/alin0725/article/details/1543860

http://www.docin.com/p-109645877.html

http://vaero.blog.51cto.com/4350852/822997

http://www.cnblogs.com/drizzlecrj/archive/2008/02/25/1077494.html

http://blog.chinaunix.net/uid-27105712-id-3270143.html
