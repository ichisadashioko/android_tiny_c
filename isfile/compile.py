import os
import subprocess
import traceback


def execute_shell_command(
    cmd: str,
    cwd=None,
    timeout=5,
):
    retval = {
        'input': {
            'command': cmd,
            'cwd': cwd,
            'timeout': timeout,
        },
        'process': None,
        'stdout': None,
        'stderr': None,
        'returncode': None,
        'exception': None,
        'stack_trace': None,
    }

    try:
        ps = subprocess.Popen(
            cmd,
            cwd=cwd,
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
            shell=True,
        )

        retval['process'] = ps

        stdout, stderr = ps.communicate(timeout=timeout)
        retval['stdout'] = stdout
        retval['stderr'] = stderr
        retval['returncode'] = ps.returncode
    except Exception as ex:
        stack_trace = traceback.format_exc()
        retval['exception'] = ex
        retval['stack_trace'] = stack_trace

    return retval


MODULE_PARENT = os.path.dirname(os.path.abspath(__file__))
output_dir = os.path.join(MODULE_PARENT, 'out')
executable_name = 'isfile'
executable_path = os.path.join(output_dir, executable_name)

if not os.path.exists(output_dir):
    os.makedirs(output_dir)


if os.path.exists(executable_path):
    os.remove(executable_path)

compile_command = f'gcc -o {executable_path} main.c'
compile_command_return_value = execute_shell_command(
    cmd=compile_command,
    cwd=MODULE_PARENT,
)

print(compile_command_return_value)
