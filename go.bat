@echo on
git add . && git commit -m %date:~0,10% && git push
