import subprocess
import threading
import yaml
from typing import Any, Dict, Iterable, Union

returncodes = {}

def execute_script(script_or_scripts: Union[str, Iterable[str]]):
    if isinstance(script_or_scripts, str):
        process = subprocess.run(script_or_scripts.split())
        return process.returncode
    elif isinstance(script_or_scripts, Iterable):
        for script in script_or_scripts:
            returncode = execute_script(script)
            if returncode != 0:
                return returncode
        return 0
    else:
        raise ValueError(f"`script_or_scripts` must be a string or iterable of strings, not '{type(script_or_scripts)}'")

def execute_job(job: Dict[str, Any]):
    returncodes[job["name"]] = execute_script(job["script"])

if __name__ == "__main__":
    config = yaml.safe_load(open(".travis.yml"))
    threads = [
        threading.Thread(target=execute_job, args=(job, ))
        for job in config["jobs"]["include"]
    ]
    [thread.start() for thread in threads]
    [thread.join() for thread in threads]
    [print(job["name"], returncodes[job["name"]]) for job in config["jobs"]["include"]]
