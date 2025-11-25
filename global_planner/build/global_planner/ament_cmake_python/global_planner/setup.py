from setuptools import find_packages
from setuptools import setup

setup(
    name='global_planner',
    version='0.0.1',
    packages=find_packages(
        include=('global_planner', 'global_planner.*')),
)
