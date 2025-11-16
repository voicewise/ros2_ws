from setuptools import find_packages
from setuptools import setup

setup(
    name='puppy_control_msgs',
    version='0.0.0',
    packages=find_packages(
        include=('puppy_control_msgs', 'puppy_control_msgs.*')),
)
