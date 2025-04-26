from setuptools import find_packages
from setuptools import setup

setup(
    name='race_orchestrator',
    version='0.0.0',
    packages=find_packages(
        include=('race_orchestrator', 'race_orchestrator.*')),
)
