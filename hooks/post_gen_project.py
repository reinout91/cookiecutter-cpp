"""Post-project generation hooks"""
import os
import shutil

if __name__ == '__main__':
    """Initialize a git repository based on the configured branch and repo"""
    url    = 'git@github.com:{{ cookiecutter.username }}/{{ cookiecutter.repo_name }}'
    branch = '{{ cookiecutter.branch }}'
    remote = '{{ cookiecutter.remote }}'

    import subprocess
    subprocess.call(('git', 'init'))
    subprocess.call(('git', 'checkout', '-b', branch))
    subprocess.call(('git', 'remote', 'add', remote, url))
    if os.name == 'nt':
        shutil.move('pre-commit', '.git\\hooks')
    else:
        subprocess.call(('mv', 'pre-commit', '.git/hooks/'))
        
