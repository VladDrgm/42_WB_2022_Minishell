# 42_WB_2022_Minishell

Working Repo for the Minishell project.

Approach:

Create Issue
	Issue (task) convention:
	1) Action: Add, Create, Implement, Modify, Debug, Close
	2) Feature / Function / File name
	Example:	Implement History
				Add Makefile
				Create s_to_l()

Create Branch
	Branch Creation:
		```git branch [BRANCH_NAME]```
	Switch to branch:
		```git checkout [BRANCH_NAME]```
	Pushing created Branch:
		```git push --set-upstream origin [BRANCH_NAME]```
	Pull request:
		Do it on Github
	**Branching convention for [BRANCH_NAME]:
	1) Use your [PERSONAL_ID] (made out of 3 digits)
		[PERSONAL ID]:
			005 - Maggi
			099 - Vlad
			007 - Domen
			549 - Deki
	2) Use Issue Hash number
	3) Action: Add, Create, Implement, Modify, Debug, Close
	4) Feature / Function / File name
	Example:	007-069-Implement History
				005-555-Add Makefile
				001-969-Create s_to_l()**

Move commit from overmind to new branch (for dummys)
	Creat new branch:
		```git branch [BRANCH_NAME]```
		```git merge overmind```
		```git checkout overmind```
		```git reset --hard HEAD~[N]``` # Go back [N] commits. You *will* lose uncommitted work. [N] is a number.
		```git checkout [BRANCH_NAME]```


Add and Commit:
	Commits convention:
		1) Add a description (free to add however you want it)
		2) Write "Fixes" + {}-> github issue number (#number)
		Example: "I have fixed this thing. Fixes #4"


Installing reqierments:
-install readline library
	linux debian(based):	
	```apt-get install libreadline-dev```

