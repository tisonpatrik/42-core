/* AWS EC2 on-demand, Linux, us-east-1.
   instances.vantage.sh/aws/ec2/c7i.xlarge, updated 18 Nov 2026.
   c7i scales linearly with vCPU (c7i.large = 0.08925 $/h = half). */

Talk.data.aws = {
	instance: 'c7i.xlarge',
	vcpu: 4,
	cpu: 'Intel Xeon',
	hourly: 0.1785,
	hoursPerYear: 8760,
	baseServers: 10,   // what the clean-code version needs
	horizonYears: 5,
	compareTo: 'table', // headline: clean code vs. this Casey step
	sources: [
		['instances.vantage.sh/aws/ec2/c7i.xlarge', 'https://instances.vantage.sh/aws/ec2/c7i.xlarge'],
		['aws.amazon.com/ec2/pricing', 'https://aws.amazon.com/ec2/pricing/on-demand/'],
	],
};
