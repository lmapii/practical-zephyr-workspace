
# West workspace monorepo

This is an example for a "non-idiomatic" West workspace application. I call it "non-idomatic" since at - the time of its creation and with `west` version `1.0.0` - it is not possible to create the same workspace layout with `west init -m <this-repo-url>`. It is only possible to `git clone` this repository manually and initialize it with `west init --local app`

The goal of this repository is to have a single repository for your application. The repository is used to create a West workspace application, where files and folders are in the _workspace root location_:

```bash
$ git clone -this-repository- .
$ PIPENV_VENV_IN_PROJECT=1 pipenv install --dev
$ pipenv shell
$ west init --local app
$ west update

# creates the following layout:
$ tree --charset=utf-8 --dirsfirst -a -L 2
.
├── .git
├── .github
├── .vscode
│   └── settings.json
├── .west
│   └── config
├── app
│   ├── boards
│   ├── src
│   ├── CMakeLists.txt
│   ├── prj.conf
│   ├── ...
│   └── west.yml
├── deps
│   ├── modules
│   └── zephyr
├── .gitignore
├── readme.md
└── sdk-setup.sh
```

You can now open the root folder in an editor such as `vscode` and have the entire workspace set up without having to use another repository, e.g., for `.vscode`. Also, you can have files such as `setup.cfg` or `.pylintrc` in the root of the workspace, which are typically automatically picked up by `vscode` or other editors.

In an idiomatic workspace application, the `app` folder would be the manifest repository and at least `.west` is always located next to the folder containing the manifest file.
