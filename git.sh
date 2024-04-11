#git提交脚本 source git.sh ${提交的文件} "comment描述"
rm -rf build
git add $1
git commit -m $2
git push